#include "minesweeper.h"

#include <QRandomGenerator>
#include <QMessageBox>
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
    progress_bar = new ProgressBar(this, 35, bombs_count);
    progress_bar->setResetButtonOpacity(0.25);
    settings = new SettingsWindow(this);

    main_layout->addWidget(progress_bar);
    main_layout->setSpacing(button_size / 10);

    setupMenuBar();
    resetGame();

    main_widget->setLayout(main_layout);

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
    connect(single_game, &SingleGame::signal_setBackground, this, &Minesweeper::setBackground);

    main_layout->addWidget(single_game);
    main_layout->setAlignment(single_game, Qt::AlignCenter);

    progress_bar->resetProgress(bombs_count, 35);
    progress_bar->setResetButtonOpacity(0.25);

    this->setStyleSheet("QMainWindow {"
                            "background-color: dimgray;"
                            "}"
                        );
    menuBar()->setStyleSheet("QMenuBar {"
                                 "background-color: #3a3a3a;"
                                 "color: white;"
                             "}");

    this->adjustSize();
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
    msgbx->setTextFormat(Qt::RichText);
    msgbx->setStyleSheet("QMessageBox, QLabel {"
                            "background-color: dimgray;"
                            "color: white;"
                         "}");
    msgbx->setText("<p align=center>"
                   "<h1>QtMinesweeper</h1>"
                   "<h3>Written in march 2020 <br/>by Przemysław Majerczak (<a href=\"mailto:przmajerczak@gmail.com\">przmajerczak@gmail.com</a>)</h3>"

                   "<table>"
                   "<th><h4>Sources of elements used:</h4></th>"
                   "<tr><td><h6>Bomb icon:</h6></td><td><h6><a href=\"https://www.pngfuel.com/free-png/cdtpe\">https://www.pngfuel.com/free-png/cdtpe</a></h6></td></tr>"
                   "<tr><td><h6>Digital 7 Font:</h6></td><td><h6><a href=\"https://www.dafont.com/digital-7.font\">https://www.dafont.com/digital-7.font</a></h6></td></tr>"
                   "<tr><td><h6>Defeat background:</h6></td><td><h6><a href=\"https://commons.wikimedia.org/wiki/File:Operation_Upshot-Knothole_-_Badger_001.jpg\">https://commons.wikimedia.org</a></h6></td></tr>"
                   "<tr><td><h6>Victory background:</h6></td><td><h6><a href=\"https://commons.wikimedia.org/wiki/File:Raising_the_Flag_on_Iwo_Jima,_larger_-_edit1.jpg\">https://commons.wikimedia.org</a></h6></td></tr>"
                   "</table>"

                   "</p>"
                   );

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
        x_size = 10;
        y_size = 7;
        bombs_count = 10;
        button_size = 35;
    }

    json_settings.close();
}

void Minesweeper::setBackground(bool _victory) {
    QString image = _victory ? "victory.jpg" : "defeat.jpg";

    this->setStyleSheet("QMainWindow { "
                            "border-image: url(\"res/" + image + "\");"
                        "}");
}







