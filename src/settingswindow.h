#ifndef SETTINGS_H
#define SETTINGS_H

#include <QMessageBox>

class SettingsWindow : public QMessageBox
{
    Q_OBJECT
public:
    SettingsWindow(QWidget* parent);
};

#endif // SETTINGS_H
