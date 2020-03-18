#include "minesweeper.h"

#include <QRandomGenerator>
#include <QDebug>
#include <QMessageBox>
#include <QtMath>
#include <QGraphicsOpacityEffect>
#include <QMenu>
#include <QMenuBar>

Minesweeper::Minesweeper(QWidget* parent, int _x_size, int _y_size, int _bombs_count, int _button_size) : QMainWindow(parent){
    this->x_size = _x_size;
    this->y_size = _y_size;
    this->bombs_count = _bombs_count;
    this->button_size = _button_size;
    this->single_game = nullptr;

    main_layout = new QVBoxLayout();
    main_widget = new QWidget(this);
    progress_bar = new ProgressBar(this, (40 - _button_size) / 2 + _button_size, _bombs_count);
    progress_bar->setResetButtonOpacity(0.25);

    main_layout->addWidget(progress_bar);
    main_layout->setSpacing(_button_size / 10);

    setupMenuBar();
    resetGame();

    main_widget->setLayout(main_layout);
    this->setStyleSheet("QMainWindow {"
                                                "background-color: dimgray;"
                                                "}"
                        "QMenuBar {"
                                                "background-color: #3a3a3a;"
                                                "color: white;"
                                                "}"
                        );

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
    progress_bar->setResetButtonOpacity(0.25);
}

#ifndef QT_NO_CONTEXTMENU
void Minesweeper::contextMenuEvent(QContextMenuEvent*) {
    QMenu menu(this);
    menu.addAction(exit_action);
}
#endif // QT_NO_CONTEXTMENU
void Minesweeper::setupMenuBar() {
    exit_action = new QAction("Exit", this);
    settings_action = new QAction("Settings", this);
    about_action = new QAction("About", this);
    restart_action = new QAction("Restart", this);

    connect(exit_action, &QAction::triggered, this, &QWidget::close);
    connect(settings_action, &QAction::triggered, this, &Minesweeper::settingsSlot);
    connect(about_action, &QAction::triggered, this, &Minesweeper::aboutSlot);
    connect(restart_action, &QAction::triggered, this, &Minesweeper::resetGame);

    options_menu = menuBar()->addMenu("Options");
    options_menu->addAction(restart_action);
    options_menu->addAction(settings_action);
    options_menu->addAction(exit_action);

    more_menu = menuBar()->addMenu("More");
    more_menu->addAction(about_action);
}
void Minesweeper::aboutSlot() {
    QMessageBox* msgbx = new QMessageBox(this);
    msgbx->setWindowTitle("About");
    msgbx->setText("many many infos");
    msgbx->exec();
}
void Minesweeper::settingsSlot() {
    SettingsWindow settings(this, x_size, y_size, bombs_count, button_size);
    settings.exec();
}

