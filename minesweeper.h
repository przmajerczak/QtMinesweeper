#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include "mswprbutton.h"

#include <QMainWindow>
#include <QFrame>
#include <QGridLayout>
#include <QLabel>
#include <QSignalMapper>

class Minesweeper : public QMainWindow {

    Q_OBJECT

public:
    Minesweeper(QWidget* parent, int x_size, int y_size, int bombs_count);
public slots:
    void fieldLeftClicked(int _arg);
    void fieldMiddleClicked(int _arg);
    void fieldRightClicked(int _arg);
    void onResize();

    void resizeEvent(QResizeEvent* event) override;
signals:
    void resized();
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
    QLabel* left_label;
    QLabel* right_label;
    QVBoxLayout* main_layout;
    QHBoxLayout* box;
    QGridLayout* grid;
    QWidget* main_widget;
    QSignalMapper* sgnmap_left;
    QSignalMapper* sgnmap_middle;
    QSignalMapper* sgnmap_right;


    bool isWon();
    void drawBombs(int _arg);
    void fillWithNumbers();
    void uncoverEmpty(int field_x, int field_y);


};

#endif // MINESWEEPER_H
