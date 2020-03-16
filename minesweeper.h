#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include "mswprbutton.h"
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
private:
    QVBoxLayout* main_layout;
    QWidget* main_widget;
    ProgressBar* progress_bar;


};

#endif // MINESWEEPER_H
