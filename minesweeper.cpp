#include "minesweeper.h"

#include <QRandomGenerator>


#include <QDebug>
#include <QMessageBox>

Minesweeper::Minesweeper(QWidget* parent, int x_size, int y_size, int bombs_count) : QWidget(parent){
    this->board_x_size = x_size;
    this->board_y_size = y_size;
    this->bombs_left = this->bombs_count = bombs_count;
    this->fields_left_uncovered = board_x_size * board_y_size;
    this->button_size = 30;     // to be set as settable parameter later

    // create board of fields
    board = QVector<QVector<QSharedPointer<MswprButton>>>();
    for (int i = 0; i < board_y_size; ++i) {
        QVector<QSharedPointer<MswprButton>> temp_vect = QVector<QSharedPointer<MswprButton>>();
        for (int j = 0; j < board_x_size; ++j)
            temp_vect.push_back(QSharedPointer<MswprButton>(new MswprButton(this, j, i)));
        board.push_back(temp_vect);
    }

    drawBombs();
    fillWithNumbers();

    grid = new QGridLayout(this);
    grid->setSpacing(0);
    this->setLayout(grid);
    sgnmap_left = new QSignalMapper(this);
    sgnmap_right = new QSignalMapper(this);

    for (auto row : board) {
        for (auto elem : row) {
            connect(elem.data(), SIGNAL(leftClicked()), sgnmap_left, SLOT(map()));
            connect(elem.data(), SIGNAL(rightClicked()), sgnmap_right, SLOT(map()));

            sgnmap_left->setMapping(elem.data(), elem->getY() * board_x_size + elem->getX());
            sgnmap_right->setMapping(elem.data(), elem->getY() * board_x_size + elem->getX());

            elem->setFixedSize(button_size, button_size);
            grid->addWidget(elem.data(), elem->getY(), elem->getX());
        }
    }

    connect(sgnmap_left, SIGNAL(mapped(int)), this, SLOT(fieldLeftClicked(int)));
    connect(sgnmap_right, SIGNAL(mapped(int)), this, SLOT(fieldRightClicked(int)));


}
void Minesweeper::drawBombs() {
    // create list of numbers from 0 to the number of fields
    QList<int> board_indexes;
    for (int i = 0; i < (this->board_x_size)*(this->board_y_size); ++i)
        board_indexes.append(i);

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
    }

    qDebug() << "Bombs_left: " << bombs_left << "\tFields_left: " << fields_left_uncovered;

}
void Minesweeper::fieldRightClicked(int _arg) {
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
    }


    qDebug() << "Bombs_left: " << bombs_left << "\tFields_left: " << fields_left_uncovered;
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
