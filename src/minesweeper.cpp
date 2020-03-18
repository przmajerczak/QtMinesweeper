#include "minesweeper.h"

#include <QRandomGenerator>
#include <QDebug>
#include <QMessageBox>
#include <QtMath>
#include <QGraphicsOpacityEffect>
#include <QMenu>
#include <QMenuBar>
#include <QJsonDocument>
#include <QJsonObject>

Minesweeper::Minesweeper(QWidget* parent) : QMainWindow(parent){
    readSettings();

    this->single_game = nullptr;

    main_layout = new QVBoxLayout();
    main_widget = new QWidget(this);
    progress_bar = new ProgressBar(this, 35/*(40 - button_size) / 2 + button_size*/, bombs_count);
    progress_bar->setResetButtonOpacity(0.25);
    settings = new SettingsWindow(this);

    main_layout->addWidget(progress_bar);
    main_layout->setSpacing(button_size / 10);
    main_layout->setSizeConstraint(QLayout::SetFixedSize);

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
    connect(settings, &SettingsWindow::restartSignal, this, &Minesweeper::resetGame);

}

void Minesweeper::resetGame() {
    if (single_game != nullptr) {
        single_game->deleteLater();
    }

    readSettings();
    single_game = new SingleGame(this, progress_bar, x_size, y_size, bombs_count, button_size);

    main_layout->addWidget(single_game);
    main_layout->setAlignment(single_game, Qt::AlignCenter);

    progress_bar->resetProgress(bombs_count, 35);
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


    settings->exec();
}
void Minesweeper::readSettings() {
    QFile json_settings("res/settings.json");

    if (json_settings.open(QIODevice::ReadOnly | QIODevice::Text)) {
       QJsonDocument json_doc(QJsonDocument::fromJson(json_settings.readAll()));

       QJsonObject json_obj = json_doc.object();

       x_size = json_obj["x_size"].toInt();
       y_size = json_obj["y_size"].toInt();
       bombs_count = json_obj["bombs_count"].toInt();
       button_size = json_obj["button_size"].toInt();
    } else {
        x_size = 8;
        y_size = 8;
        bombs_count = 16;
        button_size = 35;
    }

    json_settings.close();
}

