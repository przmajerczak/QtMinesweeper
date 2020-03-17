#include "progressbar.h"

#include <QFontDatabase>
#include <QPainter>
#include <QStyleOption>
#include <QDebug>

ProgressBar::ProgressBar(QWidget* parent, int _size, int _bombs_left) : QWidget(parent) {
    size = _size;
    double text_height_factor = 0.5;

    left_label = new QLabel("BOMBS LEFT: " + QString::number(_bombs_left));
    right_label = new QLabel("PROGRESS: 0%");
    reset_button = new QPushButton(this);

    QFontDatabase::addApplicationFont("res/digital-7-italic.ttf");
    label_font = new QFont("Digital-7", size * text_height_factor);

    reset_icon = new QIcon("res/arrow.svg");
    reset_button->setIcon(*reset_icon);

    left_label->setFont(*label_font);
    right_label->setFont(*label_font);

    setFixedHeight(size);
    setStyleSheet("ProgressBar {"
                                   "background-color: #1a1a1a;"
                                   "border-radius: 4%;"
                                   "border-width: " + QString::number(size / 10) + "px;"
                                   "border-style: solid;"
                                   "border-color: black;"
                                   "}"
                  "QLabel {"
                                   "color: yellow;"
                                   "}"
                  "QPushButton {"
                                    "background-color: yellow;"//#131313;"
                                    "border-radius: 4%;"
                                    "border-width: " + QString::number(size / 20) + "px;"
                                    "border-style: solid;"
                                    "border-color: yellow;"
                                    "border-top: none;"
                                    "border-bottom: none;"
                                    "}"
                                      );

    left_label->setAlignment(Qt::AlignVCenter);
    right_label->setAlignment(Qt::AlignVCenter | Qt::AlignRight);

    left_label->setFixedWidth(4.5 * size);
    right_label->setFixedWidth(4.5 * size);
    reset_button->setFixedSize(text_height_factor * size, text_height_factor * size);
    reset_button->setIconSize(QSize(size, size));

    box = new QHBoxLayout();
    box->setContentsMargins(size * (1 - text_height_factor) / 2, 0, size * (1 - text_height_factor) / 2, 0);
    box->setSpacing(size);
    box->addWidget(left_label, 0, Qt::AlignLeft);
    box->addWidget(reset_button, 0, Qt::AlignCenter);
    box->addWidget(right_label, 0, Qt::AlignRight);

    setLayout(box);

    connect(reset_button, &QPushButton::released, this, &ProgressBar::resetGameSignalEmitter);
}
void ProgressBar::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
void ProgressBar::bombCounter(int _bombs) {
    left_label->setText("BOMBS LEFT: " + QString::number(_bombs));
}
void ProgressBar::progressCounter(int _progress) {
    right_label->setText("PROGRESS: " + QString::number(_progress) + "%");
}
void ProgressBar::setResetButtonOpacity(double _value) {
    opacity_effect = new QGraphicsOpacityEffect();
    opacity_effect->setOpacity(_value);
    reset_button->setGraphicsEffect(opacity_effect);
    reset_button->setAutoFillBackground(true);
    reset_button->setStyleSheet("QPushButton {"
                                          "border-radius: 4%;"
                                          "}");
}
void ProgressBar::resetGameSignalEmitter() {
    emit signal_resetGame();
}

void ProgressBar::resetProgress(int _bombs_left) {
    left_label->setText("BOMBS LEFT: " + QString::number(_bombs_left));
    right_label->setText("PROGRESS: 0%");
}
