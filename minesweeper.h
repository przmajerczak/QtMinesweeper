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
    void fieldLeftClicked(int _arg);
    void fieldRightClicked(int _arg);

private:
    int dsf;
    int board_x_size;
    int board_y_size;
    int bombs_left;
    int bombs_count;
    int fields_left_uncovered;
    int button_size;
    bool first_click_made;
    QVector<QVector<QSharedPointer<MswprButton>>> board;
    QGridLayout* grid;
    QSignalMapper* sgnmap_right;
    QSignalMapper* sgnmap_left;



    bool isWon();
    void drawBombs(int _arg);
    void fillWithNumbers();
    void uncoverEmpty(int field_x, int field_y);


};

#endif // MINESWEEPER_H
