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
    void resize(int _size);

public slots:
    void paintEvent(QPaintEvent *) override;
    void bombCounter(int _bombs);
    void progressCounter(int _progress);
    void setResetButtonOpacity(double _value);
    void resetProgress(int _bombs_left, int _size);

signals:
    void signal_resetGame();

private slots:
    void resetGameSignalEmitter();

private:
    int vertical_size;
    double text_height_factor;
    QHBoxLayout* box;
    QFont* label_font;
    QLabel* left_label;
    QLabel* right_label;
    QPushButton* reset_button;
    QIcon* reset_icon;
    QGraphicsOpacityEffect* opacity_effect;
};

#endif // PROGRESSBAR_H
