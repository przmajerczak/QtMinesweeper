#ifndef MSWPRBUTTON_H
#define MSWPRBUTTON_H

#include <QPushButton>


enum mswprBtn_state {
    empty,
    _1, _2, _3, _4, _5, _6, _7, _8,
    bomb
};

class MswprButton : QPushButton {
public:
    MswprButton(QWidget* parent, int _x_id, int _y_id, bool is_bomb = false);
    void setState(mswprBtn_state _stt);
    mswprBtn_state getState();

private:
    int id_x;
    int id_y;
    mswprBtn_state state;
    bool is_covered;
};

#endif // MSWPRBUTTON_H
