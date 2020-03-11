#include "mswprbutton.h"

#include <QDebug>

MswprButton::MswprButton(QWidget* parent, int _x_id, int _y_id, bool is_bomb) : QPushButton(parent) {
    this->id_x = _x_id;
    this->id_y = _y_id;
    this->state = is_bomb ? bomb : empty;
    this->neighbouring_bombs = 0;
    this->checked = false;
    this->covered = true;

    this->setStyleSheet("QPushButton { background-color: darkgrey;}");
}

int MswprButton::getX() {
    return this->id_x;
}

int MswprButton::getY() {
    return this->id_y;
}

void MswprButton::setState(mswprBtn_state _stt) {
    this->state = _stt;

    switch (this->state) {
    case bomb:
        text = "B";
        break;
    case number:
        text = QString::number(neighbouring_bombs);
        break;
    default:
        break;
    };
}

mswprBtn_state MswprButton::getState() {
    return this->state;
}

void MswprButton::increaseBombsCount() {
    neighbouring_bombs++;
    setState(number);
}
void MswprButton::clicked(Qt::MouseButton MsBtn) {
    if (covered) {
        if (MsBtn == Qt::LeftButton) {
            if (!checked) {
                covered = false;
                this->setText(text);
                this->setStyleSheet("QPushButton {background-color: gainsboro;}");
            }
        } else if (MsBtn == Qt::RightButton) {
            checked = !checked;
            if (checked)
                this->setText("C");
            else
                this->setText("");
        }
    }
}

void MswprButton::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::RightButton)
        emit rightClicked();
    else if (event->button() == Qt::LeftButton)
        emit leftClicked();
}

bool MswprButton::isCovered() const {
    return this->covered;
}

bool MswprButton::isChecked() const {
    return this->checked;
}
