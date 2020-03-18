#include "settingswindow.h"

#include <QDebug>

SettingsWindow::SettingsWindow(QWidget* parent, int _x_size, int _y_size, int _bombs_count, int _button_size) : QDialog(parent)
{
    qDebug() << _x_size << ' ' << _y_size << ' ' << _bombs_count << ' ' << _button_size;

    this->x_size = _x_size;
    this->y_size = _y_size;
    this->bombs_count = _bombs_count;
    this->button_size = _button_size;

    main_layout = new QVBoxLayout();

    setupBoardSize();
    setupBombs();
    setupButtonSize();
    setupControlButtons();

    this->setLayout(main_layout);
}
void SettingsWindow::setupBoardSize() {
    board_size_layout = new QHBoxLayout();
    board_size_box = new QGroupBox("Board size", this);
    x_size_combo = new QComboBox(this);
    y_size_combo = new QComboBox(this);
    x_size_label = new QLabel("Fields horizontally:");
    y_size_label = new QLabel("Fields vertically:");


    board_size_layout->addWidget(x_size_label);
    board_size_layout->addWidget(x_size_combo);
    board_size_layout->addWidget(y_size_label);
    board_size_layout->addWidget(y_size_combo);

    board_size_box->setLayout(board_size_layout);
    main_layout->addWidget(board_size_box);
}
void SettingsWindow::setupBombs() {
    bombs_layout = new QHBoxLayout();
    bombs_box = new QGroupBox("Bombs", this);
    bomb_slider = new QSlider(Qt::Horizontal,this);
    bomb_slider_min_percent_label = new QLabel(QString::number(100 / (x_size * y_size)) + "%");
    bomb_slider_max_percent_label = new QLabel(QString::number(100 * (x_size * y_size - 9) / (x_size * y_size)) + "%");
    bomb_count_label = new QLabel("X bombs");

    bombs_layout->addWidget(bomb_slider_min_percent_label, 0);
    bombs_layout->addWidget(bomb_slider, 10);
    bombs_layout->addWidget(bomb_slider_max_percent_label, 0);
    bombs_layout->addWidget(bomb_count_label, 3, Qt::AlignRight);

    bombs_box->setLayout(bombs_layout);
    main_layout->addWidget(bombs_box);
}
void SettingsWindow::setupButtonSize() {
    button_size_layout = new QHBoxLayout();
    button_size_box = new QGroupBox("Single field size", this);
    button_size_combo = new QComboBox(this);
    button_size_box->setLayout(button_size_layout);
    button_size_layout->addWidget(button_size_combo);
    main_layout->addWidget(button_size_box);
}
void SettingsWindow::setupControlButtons() {
    control_buttons_layout = new QHBoxLayout(this);
    control_buttons_widget = new QWidget(this);
    apply_restart_button = new QPushButton("Save, apply and \nrestart game", this);
    apply_later_button = new QPushButton("Save and finish\ncurrent game", this);
    cancel_button = new QPushButton("Cancel", this);

    connect(cancel_button, &QPushButton::released, this, &QDialog::close);

    control_buttons_layout->addWidget(cancel_button);
    control_buttons_layout->addWidget(apply_later_button, 1, Qt::AlignRight);
    control_buttons_layout->addWidget(apply_restart_button, 0, Qt::AlignRight);

    control_buttons_widget->setLayout(control_buttons_layout);
    main_layout->addWidget(control_buttons_widget);
}
/*

QJsonObject json_obj;
json_obj["margin"] = 10;
json_obj["bombs"] = 20;
json_obj["background_color"] = "grey";

QJsonDocument json_doc(json_obj);

QFile jsonfile("config.json");
jsonfile.open(QFile::WriteOnly);
jsonfile.write(json_doc.toJson());
jsonfile.close();

*/
