#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include "mswprbutton.h"

#include <QFrame>
#include <QGridLayout>
#include <QSignalMapper>

class Minesweeper : public QWidget {

    Q_OBJECT

public:
    Minesweeper(QWidget* parent, int x_size, int y_size, int bombs_count);
public slots:
    void fieldClicked(int _arg);
private:
    int dsf;
    int x;
    int y;
    int bombs_left;
    int button_size;
    QVector<QVector<QSharedPointer<MswprButton>>> board;
    QGridLayout* grid;
    QSignalMapper* sgnmap;



    bool isWon();
    void drawBombs();
    void fillWithNumbers();


};

#endif // MINESWEEPER_H
