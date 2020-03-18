#include "singlegame.h"

#include <QMessageBox>
#include <QRandomGenerator>
#include <QtMath>
#include <QDebug>

SingleGame::SingleGame(QWidget* parent, int _x_size, int _y_size, int _bombs_count, int _button_size, ProgressBar* _progress_bar) : QWidget(parent)
{
    this->board_x_size = _x_size;
    this->board_y_size = _y_size;
    this->bombs_left = this->bombs_count = _bombs_count;
    this->fields_left_uncovered = board_x_size * board_y_size;
    this->first_click_made = false;
    this->game_lost = false;
    this->button_size = _button_size;
    this->progress_bar = _progress_bar;

    grid = new QGridLayout();

    boardInit();

    grid->setSpacing(0);
    setLayout(grid);

    connect(this, &SingleGame::signal_bombCounter, progress_bar, &ProgressBar::bombCounter);
    connect(this, &SingleGame::signal_progressCounter, progress_bar, &ProgressBar::progressCounter);
    connect(this, &SingleGame::signal_setResetButtonOpacity, progress_bar, &ProgressBar::setResetButtonOpacity);
}
void SingleGame::boardInit() {
    // create board of fields
    board = QVector<QVector<QSharedPointer<MswprButton>>>();
    for (int i = 0; i < board_y_size; ++i) {
        QVector<QSharedPointer<MswprButton>> temp_vect = QVector<QSharedPointer<MswprButton>>();
        for (int j = 0; j < board_x_size; ++j)
            temp_vect.push_back(QSharedPointer<MswprButton>(new MswprButton(this, j, i)));
        board.push_back(temp_vect);
    }

    sgnmap_left = new QSignalMapper(this);
    sgnmap_middle = new QSignalMapper(this);
    sgnmap_right = new QSignalMapper(this);

    for (auto row : board) {
        for (auto elem : row) {
            connect(elem.data(), SIGNAL(leftClicked()), sgnmap_left, SLOT(map()));
            connect(elem.data(), SIGNAL(middleClicked()), sgnmap_middle, SLOT(map()));
            connect(elem.data(), SIGNAL(rightClicked()), sgnmap_right, SLOT(map()));

            sgnmap_left->setMapping(elem.data(), elem->getY() * board_x_size + elem->getX());
            sgnmap_middle->setMapping(elem.data(), elem->getY() * board_x_size + elem->getX());
            sgnmap_right->setMapping(elem.data(), elem->getY() * board_x_size + elem->getX());

            elem->setSize(button_size);
            elem->setFont(QFont("Sans Serif", button_size * 0.5, QFont::DemiBold));
            grid->addWidget(elem.data(), 1 + elem->getY(), elem->getX());
        }
    }

    connect(sgnmap_left, SIGNAL(mapped(int)), this, SLOT(fieldLeftClicked(int)));
    connect(sgnmap_middle, SIGNAL(mapped(int)), this, SLOT(fieldMiddleClicked(int)));
    connect(sgnmap_right, SIGNAL(mapped(int)), this, SLOT(fieldRightClicked(int)));
}
void SingleGame::drawBombs(int _arg) {
    // create list of numbers from 0 to the number of fields
    QList<int> board_indexes;
    for (int i = 0; i < (this->board_x_size)*(this->board_y_size); ++i)
        board_indexes.append(i);

    int field_y = _arg / board_x_size;
    int field_x = _arg % board_x_size;

    // exclude first clicked field with neighbours
    for (int i = field_x - 1; i <= field_x + 1; ++i)
        for (int j = field_y - 1; j <= field_y + 1; ++j)
            // if exist
            if (    i >= 0 && i < board_x_size &&
                    j >= 0 && j < board_y_size )
            board_indexes.removeOne(j * board_x_size + i);


    /*  draw the index of the number of field from the list
     *  mark that field it as bomb using division and modulo
     *  remove used index of the number of field
     *  repeat everything as many times as needed */
    for (int i = 0; i < this->bombs_left; ++i) {
        int random_index = QRandomGenerator::system()->bounded(board_indexes.size());
        board.value(board_indexes.at(random_index) / this->board_x_size)
                .value(board_indexes.at(random_index) % this->board_x_size)->setState(bomb);
        board_indexes.removeAt(random_index);
    }
}
void SingleGame::fillWithNumbers() {
    // for each row
    for (auto row : board)
        // for each element of that row
        for (auto elem : row)
            if (elem->getState() == bomb)
                // check all surrounding fields
                for (int i = elem->getX() - 1; i < elem->getX() + 2; ++i)
                    for (int j = elem->getY() - 1; j < elem->getY() + 2; ++j)
                        // if they exist and aren't a bomb
                        if (    i >= 0 && i < board_x_size &&
                                j >= 0 && j < board_y_size &&
                                board.at(j).at(i)->getState() != bomb)
                            // and increment they bomb counter
                            board.value(j).value(i)->increaseBombsCount();
}
void SingleGame::fieldLeftClicked(int _arg) {
    if (!first_click_made){
        drawBombs(_arg);
        fillWithNumbers();
        first_click_made = true;
    }

    int field_y = _arg / board_x_size;
    int field_x = _arg % board_x_size;
    QSharedPointer<MswprButton> field = board.value(field_y).value(field_x);

    if (field->isCovered() && !field->isChecked() && !game_lost) {

        if (field->getState() == empty) {
            uncoverEmpty(field_x, field_y);
        } else {
            field->clicked(Qt::LeftButton);
            if (field->getState() != bomb)
                fields_left_uncovered--;
        }

        if (field->getState() == bomb && !field->isChecked()) {
            this->setObjectName("main_widget");
            this->setStyleSheet("#main_widget { "
                                   "background-image: url(\"res/explosion.jpg\");"
                                   "background-position: center;"
                                   "background-repeat: no-repeat;"
                                   "}");

            emit signal_setResetButtonOpacity(1.0);
            for (auto row : board)
                for (auto elem : row)
                    if (!(elem->getX() == field_x && elem->getY() == field_y)) {
                            elem->setOpacity(0.3);
                    }

            game_lost = true;
        }

        if (this->isWon()) {
            for (auto row : board)
                for (auto elem : row)
                    if (!(elem->getState() == bomb))
                        elem->setOpacity(0.3);
            emit signal_setResetButtonOpacity(1.0);

            QMessageBox* msgbx = new QMessageBox(this);
            msgbx->setWindowTitle(":D");
            msgbx->setText("Wygrana!");
            msgbx->show();
        }

        emit signal_progressCounter(qFloor(100 * double((board_x_size * board_y_size - fields_left_uncovered)) / (board_x_size * board_y_size - bombs_count)));
    }
}
void SingleGame::fieldMiddleClicked(int _arg) {
    if (!first_click_made){
        drawBombs(_arg);
        fillWithNumbers();
        first_click_made = true;
    }

    int field_y = _arg / board_x_size;
    int field_x = _arg % board_x_size;
    QSharedPointer<MswprButton> field = board.value(field_y).value(field_x);

    if (!field->isChecked())
        for (int i = field_x - 1; i <= field_x + 1; ++i)
            for (int j = field_y - 1; j <= field_y + 1; ++j)
                // if they exist
                if (    i >= 0 && i < board_x_size &&
                        j >= 0 && j < board_y_size )
                    // aren't current field
                    //if (!(i == field_x && j == field_y))
                        // and are clickable
                        fieldLeftClicked(j * board_x_size + i);
}
void SingleGame::fieldRightClicked(int _arg) {
    if (first_click_made) {
        int field_y = _arg / board_x_size;
        int field_x = _arg % board_x_size;
        QSharedPointer<MswprButton> field = board.value(field_y).value(field_x);

        if (field->isCovered() && !game_lost) {
            field->clicked(Qt::RightButton);

            if (field->isChecked())
                bombs_left--;
            else
                bombs_left++;

            emit signal_bombCounter(bombs_left);
        }
    }
}
bool SingleGame::isWon() {
    return fields_left_uncovered == bombs_count;
}
void SingleGame::uncoverEmpty(int field_x, int field_y) {

    // click the field
    board.value(field_y).value(field_x)->clicked(Qt::LeftButton);
    this->fields_left_uncovered--;


    // if empty, call this method on the neighbours
    if (board.value(field_y).value(field_x)->getState() == empty) {
        for (int i = field_x - 1; i <= field_x + 1; ++i)
            for (int j = field_y - 1; j <= field_y + 1; ++j)
                // if they exist
                if (    i >= 0 && i < board_x_size &&
                        j >= 0 && j < board_y_size )
                    // aren't current field
                    if (!(i == field_x && j == field_y))
                        // and are clickable
                        if (board.value(j).value(i)->isCovered())
                            if (!board.value(j).value(i)->isChecked())
                                uncoverEmpty(i, j);
    }
}
