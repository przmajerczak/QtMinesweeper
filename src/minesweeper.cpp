#include "minesweeper.h"

#include <QRandomGenerator>
#include <QDebug>
#include <QMessageBox>
#include <QtMath>
#include <QGraphicsOpacityEffect>

Minesweeper::Minesweeper(QWidget* parent, int _x_size, int _y_size, int _bombs_count, int _button_size) : QMainWindow(parent){
    this->x_size = _x_size;
    this->y_size = _y_size;
    this->bombs_count = _bombs_count;
    this->button_size = _button_size;

    main_layout = new QVBoxLayout();
    main_widget = new QWidget(this);
    progress_bar = new ProgressBar(this, (40 - _button_size) / 2 + _button_size, _bombs_count);
    progress_bar->setResetButtonOpacity(0.25);

    main_layout->addWidget(progress_bar);
    main_layout->setSpacing(_button_size / 10);

    resetGame();

    main_widget->setLayout(main_layout);
    this->setStyleSheet("QMainWindow {"
                        "background-color:dimgray;"
                        "}");

    this->setCentralWidget(main_widget);

    connect(progress_bar, &ProgressBar::signal_resetGame, this, &Minesweeper::resetGame);
}

void Minesweeper::resetGame() {
    if (single_game != nullptr) {
        single_game->deleteLater();
    }
    single_game = new SingleGame(this, x_size, y_size, bombs_count, button_size, progress_bar);

    main_layout->addWidget(single_game);
    main_layout->setAlignment(single_game, Qt::AlignCenter);

    progress_bar->resetProgress(bombs_count);
}
