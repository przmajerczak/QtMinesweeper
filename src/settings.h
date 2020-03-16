#ifndef SETTINGS_H
#define SETTINGS_H

#include <QFrame>
#include <QWidget>

class Settings : public QWidget
{
    Q_OBJECT
public:
    Settings();
private:
    QFrame* main_frame;
};

#endif // SETTINGS_H
