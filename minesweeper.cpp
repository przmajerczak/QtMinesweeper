#include "minesweeper.h"

#include <QRandomGenerator>
#include <QDebug>
#include <QMessageBox>
#include <QtMath>
#include <QGraphicsOpacityEffect>

Minesweeper::Minesweeper(QWidget* parent, int _x_size, int _y_size, int _bombs_count, int _button_size) : QMainWindow(parent){
    main_layout = new QVBoxLayout();
    main_widget = new QWidget(this);
    progress_bar = new ProgressBar(this, (40 - _button_size) / 2 + _button_size, _bombs_count);
    progress_bar->setResetButtonOpacity(0.25);

    ///////
    auto gam = new SingleGame(parent, _x_size, _y_size, _bombs_count, _button_size, progress_bar);

    main_layout->addWidget(progress_bar);
    main_layout->addWidget(gam);
    //main_layout->addLayout(grid);
    main_layout->setSpacing(_button_size / 10);
    main_layout->setAlignment(gam, Qt::AlignCenter);
    main_widget->setLayout(main_layout);
    this->setStyleSheet("QMainWindow {"
                        "background-color:dimgray;"
                        "}");

    this->setCentralWidget(main_widget);
}
