#include "minesweeper.h"

Minesweeper::Minesweeper(QWidget* parent, int x_size, int y_size, int bombs_count) : QWidget(parent){
    this->x = x_size;
    this->y = y_size;
    this->bombs_left = bombs_count;
/*
    board = QVector<QVector<MswprButton>>(y);

    for (int i = 0; i < y; ++i) {
        for (int j = 0; j < x; ++j)
            board.value(i).push_back(MswprButton(this, j, i));
    }*/



}
