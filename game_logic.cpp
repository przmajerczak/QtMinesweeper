#include "game_logic.h"

#include <random>


MswprButton::MswprButton(QWidget* parent, int _x_id, int _y_id, bool is_bomb) : QPushButton(parent) {
    this->id_x = _x_id;
    this->id_y = _y_id;
    this->is_covered = true;
    this->state = is_bomb ? bomb : empty;
}

Minesweeper::Minesweeper(QWidget* parent, int x_size, int y_size, int bombs_count) : QWidget(parent){
    this->x = x_size;
    this->y = y_size;
    this->bombs_left = bombs_count;

    board = QVector<QVector<MswprButton>>(y);

    for (int i = 0; i < y; ++i) {
        for (int j = 0; j < x; ++j)
            board.value(i).push_back(MswprButton(this, j, i));
    }



}
