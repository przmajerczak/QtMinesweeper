#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>

class ProgressBar : public QWidget
{
    Q_OBJECT
public:
    ProgressBar(QWidget* parent, int _size, int _bombs_left);
public slots:
    void paintEvent(QPaintEvent *);
    void bombsLeft(int _bombs);
private:
    int size;
    QHBoxLayout* box;
    QFont* font;
    QLabel* left_label;
    QLabel* right_label;

    };

#endif // PROGRESSBAR_H
