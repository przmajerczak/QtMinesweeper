#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include "mswprbutton.h"

#include <QWidget>

class Minesweeper : public QWidget{
    Q_OBJECT
public:
    Minesweeper(QWidget* parent, int x_size, int y_size, int bombs_count);
private slots:
    void fieldClicked();
private:
    int x;
    int y;
    int bombs_left;
    QList<QList<MswprButton*>> board;
    bool isWon();


};

#endif // MINESWEEPER_H
