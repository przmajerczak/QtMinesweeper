#include "minesweeper.h"

#include <QRandomGenerator>
#include <QDebug>
#include <QFontDatabase>
#include <QMessageBox>
#include <QtMath>

Minesweeper::Minesweeper(QWidget* parent, int x_size, int y_size, int bombs_count) : QMainWindow(parent){
    this->board_x_size = x_size;
    this->board_y_size = y_size;
    this->bombs_left = this->bombs_count = bombs_count;
    this->fields_left_uncovered = board_x_size * board_y_size;
    this->first_click_made = false;
    this->button_size = 30;     // to be set as settable parameter later

    grid = new QGridLayout();
    main_layout = new QVBoxLayout();
    main_widget = new QWidget(this);
    progressBar = new ProgressBar(this, button_size, bombs_left);

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

    grid->setSpacing(0);


    main_layout->addWidget(progressBar);
    main_layout->addLayout(grid);
    main_layout->setSpacing(button_size / 10);
    main_layout->setAlignment(grid, Qt::AlignCenter);
    main_widget->setLayout(main_layout);
    this->setStyleSheet("QMainWindow {background-color:dimgray;}");

    this->setCentralWidget(main_widget);

    connect(this, SIGNAL(resized()), this, SLOT(onResize()));

//progressbar_widget->setStyleSheet("QWidget {background-color:blue;}");
    /*

    main_layout = new QVBoxLayout(main_widget);
    main_layout->setSpacing(button_size / 10);
    main_widget->setLayout(main_layout);
    main_layout->addLayout(box);
    main_layout->addLayout(grid);

    this->setStyleSheet("QWidget {background-color:dimgray;}");
    mainer_layout = new QBoxLayout(QBoxLayout::TopToBottom, this);
    this->setLayout(mainer_layout);
    mainer_layout->addWidget(this);
    mainer_layout->setAlignment(this, Qt::AlignCenter);
    */
}
void Minesweeper::drawBombs(int _arg) {
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
void Minesweeper::fillWithNumbers() {
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
void Minesweeper::fieldLeftClicked(int _arg) {
    if (!first_click_made){
        drawBombs(_arg);
        fillWithNumbers();
        first_click_made = true;
    }

    int field_y = _arg / board_x_size;
    int field_x = _arg % board_x_size;
    QSharedPointer<MswprButton> field = board.value(field_y).value(field_x);

    if (field->isCovered() && !field->isChecked()) {

        if (field->getState() == empty) {
            uncoverEmpty(field_x, field_y);
        } else {
            field->clicked(Qt::LeftButton);
            fields_left_uncovered--;
        }

        if (field->getState() == bomb && !field->isChecked()) {
            QMessageBox* msgbx = new QMessageBox(this);
            msgbx->setWindowTitle(":C");
            msgbx->setText("Bomba!");
            msgbx->show();
        }

        if (this->isWon()) {
            QMessageBox* msgbx = new QMessageBox(this);
            msgbx->setWindowTitle(":D");
            msgbx->setText("Wygrana!");
            msgbx->show();
        }

        right_label->setText("PROGRESS: " + QString::number(qFloor(100 - (100 * (fields_left_uncovered - bombs_count) / (board_x_size * board_y_size - bombs_count)))) + "%");
    }
}
void Minesweeper::fieldMiddleClicked(int _arg) {
    if (!first_click_made){
        drawBombs(_arg);
        fillWithNumbers();
        first_click_made = true;
    }

    int field_y = _arg / board_x_size;
    int field_x = _arg % board_x_size;
    QSharedPointer<MswprButton> field = board.value(field_y).value(field_x);

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
void Minesweeper::fieldRightClicked(int _arg) {
    if (first_click_made) {
        int field_y = _arg / board_x_size;
        int field_x = _arg % board_x_size;
        QSharedPointer<MswprButton> field = board.value(field_y).value(field_x);

        if (field->isCovered()) {
            field->clicked(Qt::RightButton);

            if (field->isChecked())
                bombs_left--;
            else
                bombs_left++;

            if (this->isWon()) {
                QMessageBox* msgbx = new QMessageBox(this);
                msgbx->setWindowTitle(":D");
                msgbx->setText("Wygrana!");
                msgbx->show();
            }

            left_label->setText("BOMBS LEFT: " + QString::number(bombs_left));
        }
    }
}
void Minesweeper::onResize() {

    qDebug() << main_widget->geometry().width();
    //qDebug() << *margin;
    //left_label->setFixedSize(1 + (main_widget->geometry().width() - 11) / 2, button_size);
    //right_label->setFixedSize(1 + (main_widget->geometry().width() - 11) / 2, button_size);
}
void Minesweeper::resizeEvent(QResizeEvent* event) {
    emit resized();
}
bool Minesweeper::isWon() {
    return fields_left_uncovered == bombs_count;
}
void Minesweeper::uncoverEmpty(int field_x, int field_y) {

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
