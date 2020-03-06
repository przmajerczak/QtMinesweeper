#include "minesweeper.h"
#include <QDebug>
Minesweeper::Minesweeper(QWidget* parent, int x_size, int y_size, int bombs_count) : QWidget(parent){
    this->x = x_size;
    this->y = y_size;
    this->bombs_left = bombs_count;

    board = QList<QList<MswprButton*>>();

    for (int i = 0; i < y; ++i) {
        board.append(QList<MswprButton*>());
        for (int j = 0; j < x; ++j) {
            board.last().append(new MswprButton(this, j, i, true));

        }
    }



}

void Minesweeper::fieldClicked() {
    ;
}
