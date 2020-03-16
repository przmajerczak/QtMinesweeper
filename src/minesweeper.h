#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include "progressbar.h"
#include "singlegame.h"

#include <QMainWindow>
#include <QFrame>
#include <QGridLayout>
#include <QLabel>
#include <QSignalMapper>

class Minesweeper : public QMainWindow {

    Q_OBJECT

public:
    Minesweeper(QWidget* parent, int _x_size, int _y_size, int _bombs_count, int _button_size);
public slots:
    void resetGame();
private:
    int x_size;
    int y_size;
    int bombs_count;
    int button_size;

    QVBoxLayout* main_layout;
    QWidget* main_widget;
    ProgressBar* progress_bar;
    SingleGame* single_game;


};

#endif // MINESWEEPER_H
