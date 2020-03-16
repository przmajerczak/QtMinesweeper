#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <QGraphicsOpacityEffect>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QWidget>

class ProgressBar : public QWidget
{
    Q_OBJECT
public:
    ProgressBar(QWidget* parent, int _size, int _bombs_left);
public slots:
    void paintEvent(QPaintEvent *);
    void bombCounter(int _bombs);
    void progressCounter(int _progress);
    void setResetButtonOpacity(double _value);
    void resetProgress(int _bombs_left);
signals:
    void signal_resetGame();
private slots:
    void resetGameSignalEmitter();
private:
    int size;
    QHBoxLayout* box;
    QFont* label_font;
    QLabel* left_label;
    QLabel* right_label;
    QPushButton* reset_button;
    QIcon* reset_icon;
    QGraphicsOpacityEffect* opacity_effect;
    };

#endif // PROGRESSBAR_H
