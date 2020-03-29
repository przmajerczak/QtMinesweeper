#include "settingswindow.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

SettingsWindow::SettingsWindow(QWidget* parent) : QDialog(parent)
{
    readSettings();

    main_layout = new QVBoxLayout();

    setupBoardSize();
    setupBombs();
    setupButtonSize();
    setupControlButtons();

    this->setStyleSheet("QDialog {"
                                                    "background-color: #acacac;"
                                                "}"

                        "QPushButton, QComboBox {"
                                                    "background-color: #cacaca;"
                                                "}"

                        );

    this->setLayout(main_layout);
}
void SettingsWindow::setupBoardSize() {
    board_size_layout = new QHBoxLayout();
    board_size_box = new QGroupBox("Board size", this);
    x_size_combo = new QComboBox(this);
    y_size_combo = new QComboBox(this);
    x_size_label = new QLabel("Fields horizontally:");
    y_size_label = new QLabel("Fields vertically:");

    for (int i = 0; i < 21; ++i) {
        x_size_combo->insertItem(i, QString::number(4 + i));
        y_size_combo->insertItem(i, QString::number(4 + i));
    }
    x_size_combo->setCurrentIndex(x_size - 4);
    y_size_combo->setCurrentIndex(y_size - 4);

    connect(x_size_combo, QOverload<int>::of(&QComboBox::activated),
            [this](int _index){this->x_size = 4 + _index;});
    connect(y_size_combo, QOverload<int>::of(&QComboBox::activated),
            [this](int _index){this->y_size = 4 + _index;});
    connect(x_size_combo, QOverload<int>::of(&QComboBox::activated),
            this, &SettingsWindow::updateBombLabels);
    connect(y_size_combo, QOverload<int>::of(&QComboBox::activated),
            this, &SettingsWindow::updateBombLabels);

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
    bomb_count_label = new QLabel(QString::number(bombs_count) + " bombs");

    bomb_slider->setMinimum(1);
    bomb_slider->setMaximum(x_size * y_size - 9);
    bomb_slider->setSliderPosition(bombs_count);


    connect(bomb_slider, &QSlider::valueChanged,
            [this](int _value){
                                    this->bombs_count = _value;
                                    bomb_count_label->setText(QString::number(bombs_count) + " bombs");
                                });

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

    button_size_combo->insertItem(0,           "Nano");
    button_size_combo->insertItem(1,   "Really small");
    button_size_combo->insertItem(2,          "Small");
    button_size_combo->insertItem(3,         "Normal");
    button_size_combo->insertItem(4,            "Big");
    button_size_combo->insertItem(5,           "Huge");
    button_size_combo->insertItem(6,       "Enormous");

    switch(button_size) {
        case 7:
            button_size_combo->setCurrentIndex(0); break;
        case 15:
            button_size_combo->setCurrentIndex(1); break;
        case 25:
            button_size_combo->setCurrentIndex(2); break;
        case 35:
            button_size_combo->setCurrentIndex(3); break;
        case 42:
            button_size_combo->setCurrentIndex(4); break;
        case 50:
            button_size_combo->setCurrentIndex(5); break;
        case 65:
            button_size_combo->setCurrentIndex(6); break;
    }

    connect(button_size_combo, QOverload<int>::of(&QComboBox::activated),
            [this](int _index){
                switch (_index) {
                    case 0:
                        this->button_size = 7; break;
                    case 1:
                        this->button_size = 15; break;
                    case 2:
                        this->button_size = 25; break;
                    case 3:
                        this->button_size = 35; break;
                    case 4:
                        this->button_size = 42; break;
                    case 5:
                        this->button_size = 50; break;
                    case 6:
                        this->button_size = 65; break;
                }
            }
    );

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

    connect(apply_restart_button, &QPushButton::released, this, &SettingsWindow::applyRestartSlot);
    connect(apply_later_button, &QPushButton::released, this, &SettingsWindow::applyLaterSlot);
    connect(cancel_button, &QPushButton::released, this, &QDialog::close);

    control_buttons_layout->addWidget(cancel_button);
    control_buttons_layout->addWidget(apply_later_button, 1, Qt::AlignRight);
    control_buttons_layout->addWidget(apply_restart_button, 0, Qt::AlignRight);

    control_buttons_widget->setLayout(control_buttons_layout);
    main_layout->addWidget(control_buttons_widget);
}

void SettingsWindow::applyRestartSlot() {
    saveSettings();
    emit restartSignal();
    this->close();
}
void SettingsWindow::applyLaterSlot() {
    saveSettings();
    this->close();
}
void SettingsWindow::updateBombLabels() {
    bomb_slider_min_percent_label->setText(QString::number(100 / (x_size * y_size)) + "%");
    bomb_slider_max_percent_label->setText(QString::number(100 * (x_size * y_size - 9) / (x_size * y_size)) + "%");
    bomb_slider->setMaximum(x_size * y_size - 9);
}
void SettingsWindow::readSettings() {
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
void SettingsWindow::saveSettings() {
    QJsonObject json_obj;

    json_obj["x_size"] = x_size;
    json_obj["y_size"] = y_size;
    json_obj["bombs_count"] = bombs_count;
    json_obj["button_size"] = button_size;

    QJsonDocument json_doc(json_obj);

    QFile jsonfile("res/settings.json");

    jsonfile.open(QIODevice::WriteOnly | QIODevice::Text);
    jsonfile.write(json_doc.toJson());
    jsonfile.close();
}
