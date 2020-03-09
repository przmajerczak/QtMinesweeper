#include "minesweeper.h"

#include <QRandomGenerator>


#include <QDebug>

Minesweeper::Minesweeper(QWidget* parent, int x_size, int y_size, int bombs_count) : QWidget(parent){
    this->x = x_size;
    this->y = y_size;
    this->bombs_left = bombs_count;




    // create board of fields
    board = QVector<QVector<QSharedPointer<MswprButton>>>();
    for (int i = 0; i < y; ++i) {
        QVector<QSharedPointer<MswprButton>> temp_vect = QVector<QSharedPointer<MswprButton>>();
        for (int j = 0; j < x; ++j)
            temp_vect.push_back(QSharedPointer<MswprButton>(new MswprButton(this, j, i, true)));
        board.push_back(temp_vect);
    }

    drawBombs();
    fillWithNumbers();

    grid = new QGridLayout(this);
    grid->setSpacing(0);
    button_size = 30;

    for (auto row : board) {
        for (auto elem : row) {
           elem->setFixedSize(button_size, button_size);
           grid->addWidget(elem.data(), elem->getY(), elem->getX());
            }
    }

    setLayout(grid);







}
void Minesweeper::drawBombs() {
    // create list of numbers from 0 to the number of fields
    QList<int> board_indexes;
    for (int i = 0; i < (this->x)*(this->y); ++i)
        board_indexes.append(i);

    /*  draw the index of the number of field from the list
     *  mark that field it as bomb using division and modulo
     *  remove used index of the number of field
     *  repeat everything as many times as needed */
    for (int i = 0; i < this->bombs_left; ++i) {
        int random_index = QRandomGenerator::system()->bounded(board_indexes.size());
        board.value(board_indexes.at(random_index) / this->x)
                .value(board_indexes.at(random_index) % this->x)->setState(bomb);
        board_indexes.removeAt(random_index);
    }
}

void Minesweeper::fillWithNumbers() {
    for (auto row : board)
        for (auto elem : row)
            if (elem->getState() == bomb)
                for (int i = elem->getX() - 1; i < elem->getX() + 2; ++i)
                    for (int j = elem->getY() - 1; j < elem->getY() + 2; ++j)
                        if (    i > 0 && i < row.size() &&
                                j > 0 && j < board.size() &&
                                board.at(j).at(i)->getState() != bomb)
                            board.at(j).at(i)->increaseBombsCount();



}

void Minesweeper::fieldClicked() {
    ;
}
