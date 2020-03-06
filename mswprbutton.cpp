#include "mswprbutton.h"

MswprButton::MswprButton(QWidget* parent, int _x_id, int _y_id, bool is_bomb) : QPushButton(parent) {
    this->id_x = _x_id;
    this->id_y = _y_id;
    this->is_covered = true;
    this->state = is_bomb ? bomb : empty;
}
