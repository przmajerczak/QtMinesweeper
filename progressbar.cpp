#include "progressbar.h"

#include <QFontDatabase>
#include <QPainter>
#include <QStyleOption>

ProgressBar::ProgressBar(QWidget* parent, int _size, int _bombs_left) : QWidget(parent)
{
    size = _size;
    double text_height_factor = 0.5;

    left_label = new QLabel("BOMBS LEFT: " + QString::number(_bombs_left));
    right_label = new QLabel("PROGRESS: iles%");

    QFontDatabase::addApplicationFont("digital-7-italic.ttf");
    font = new QFont("Digital-7", size * text_height_factor);

    left_label->setFont(*font);
    right_label->setFont(*font);

    //left_label->setFixedHeight(0.7 * size);
    //right_label->setFixedHeight(0.7 * size);



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
                                      );

    left_label->setAlignment(Qt::AlignVCenter);
    right_label->setAlignment(Qt::AlignVCenter);

    box = new QHBoxLayout();
    box->setContentsMargins(size * (1 - text_height_factor) / 2, 0, size * (1 - text_height_factor) / 2, 0);
    box->setSpacing(0);
    box->addWidget(left_label, 0, Qt::AlignLeft);
    box->addWidget(right_label, 0, Qt::AlignRight);

    setLayout(box);
}
void ProgressBar::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
void ProgressBar::bombsLeft(int _bombs) {

}
