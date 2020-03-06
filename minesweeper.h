#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include "mswprbutton.h"

#include <QWidget>

class Minesweeper : QWidget{

public:
    Minesweeper(QWidget* parent, int x_size, int y_size, int bombs_count);
private:
    int x;
    int y;
    int bombs_left;
    QVector<QVector<MswprButton>> board;
    bool isWon();
private slots:
    void fieldClicked();

};

#endif // MINESWEEPER_H
