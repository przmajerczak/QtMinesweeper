#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <QPushButton>
#include <QVector>


enum mswprBtn_state {
    empty,
    _1, _2, _3, _4, _5, _6, _7, _8,
    bomb
};

class MswprButton : QPushButton {
public:
    MswprButton(QWidget* parent, int _x_id, int _y_id, bool is_bomb = false);
    ~MswprButton();
    void setState(mswprBtn_state _stt);
    mswprBtn_state getState();

private:
    int id_x;
    int id_y;
    mswprBtn_state state;
    bool is_covered;
};

class Minesweeper : QWidget{
public:
    Minesweeper(QWidget* parent, int x_size, int y_size, int bombs_count);
    ~Minesweeper();
private:
    int x;
    int y;
    int bombs_left;
    QVector<QVector<MswprButton>> board;
    bool isWon();
private slots:
    void fieldClicked();

};

#endif // GAME_LOGIC_H
