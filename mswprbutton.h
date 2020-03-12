#ifndef MSWPRBUTTON_H
#define MSWPRBUTTON_H

#include <QPushButton>
#include <QMouseEvent>

enum mswprBtn_state {
    empty,
    bomb,
    number
};

class MswprButton : public QPushButton {

    Q_OBJECT

public:

    MswprButton(QWidget* parent, int _x_id, int _y_id, bool is_bomb = false);
    void setState(mswprBtn_state _stt);
    mswprBtn_state getState();
    int getX();
    int getY();
    void increaseBombsCount();
    void clicked(Qt::MouseButton MsBtn);
    bool isChecked() const;
    bool isCovered() const;

public slots:
    void mousePressEvent(QMouseEvent* event) override;
signals:
    void leftClicked();
    void middleClicked();
    void rightClicked();
private:
    int id_x;
    int id_y;
    int neighbouring_bombs;
    bool checked;
    bool covered;
    mswprBtn_state state;
    QString text;
};

#endif // MSWPRBUTTON_H
