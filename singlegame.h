#ifndef SINGLEGAME_H
#define SINGLEGAME_H

#include "mswprbutton.h"
#include "progressbar.h"

#include <QGridLayout>
#include <QSignalMapper>
#include <QWidget>



class SingleGame : public QWidget
{
    Q_OBJECT
public:
    SingleGame(QWidget* parent, int _x_size, int _y_size, int _bombs_count, int _button_size, ProgressBar* _progress_bar);
signals:
    void signal_bombCounter(int _bombs);
    void signal_progressCounter(int _progress);
    void signal_setResetButtonOpacity(double _value);
public slots:
    void fieldLeftClicked(int _arg);
    void fieldMiddleClicked(int _arg);
    void fieldRightClicked(int _arg);
private:
    int board_x_size;
    int board_y_size;
    int bombs_left;
    int bombs_count;
    int fields_left_uncovered;
    int button_size;
    bool first_click_made;
    bool game_lost;
    QVector<QVector<QSharedPointer<MswprButton>>> board;
    QGridLayout* grid;
    QSignalMapper* sgnmap_left;
    QSignalMapper* sgnmap_middle;
    QSignalMapper* sgnmap_right;
    ProgressBar* progress_bar;


    bool isWon();
    void boardInit();
    void drawBombs(int _arg);
    void fillWithNumbers();
    void uncoverEmpty(int field_x, int field_y);


};

#endif // SINGLEGAME_H
