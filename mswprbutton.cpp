#include "mswprbutton.h"

#include <QDebug>
#include <QGraphicsOpacityEffect>


QIcon* MswprButton::checked_icon = new QIcon("checked_icon.svg");

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

    if (state == number)
        text = QString::number(neighbouring_bombs);
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
                this->setStyleSheet("QPushButton {background-color: gainsboro;}");
                this->setText(text);

                if (state == bomb) {
                    this->setText("");
                    this->setIcon(QIcon("boom.png"));
                    this->setIconSize(QSize(0.92*button_size, 0.92*button_size));
                }
            }
        } else if (MsBtn == Qt::RightButton) {
            checked = !checked;
            if (checked) {
                this->setIcon(*checked_icon);
                this->setIconSize(QSize(1.2 * button_size, 1.2 * button_size));
            }
            else
                this->setIcon(QIcon());
        }
    }
}
void MswprButton::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::RightButton)
        emit rightClicked();
    else if (event->button() == Qt::LeftButton)
        emit leftClicked();
    else if (event->button() == Qt::MiddleButton)
        emit middleClicked();
}
bool MswprButton::isCovered() const {
    return this->covered;
}
bool MswprButton::isChecked() const {
    return this->checked;
}
void MswprButton::setSize(int _size) {
    this->button_size = _size;
    this->setFixedSize(button_size, button_size);
}
void MswprButton::setOpacity(double _value) {
    opacity_effect = new QGraphicsOpacityEffect();
    opacity_effect->setOpacity(_value);
    setGraphicsEffect(opacity_effect);
    setAutoFillBackground(true);
}
