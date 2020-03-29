#ifndef SETTINGS_H
#define SETTINGS_H

#include <QComboBox>
#include <QGroupBox>
#include <QBoxLayout>
#include <QDialog>
#include <QLabel>
#include <QPushButton>

class SettingsWindow : public QDialog
{
    Q_OBJECT

public:
    SettingsWindow(QWidget* parent);

signals:
    void restartSignal();

private slots:
    void applyRestartSlot();
    void applyLaterSlot();
    void updateBombLabels();

private:
    int x_size;
    int y_size;
    int bombs_count;
    int button_size;

    QVBoxLayout* main_layout;
    QHBoxLayout* board_size_layout;
    QHBoxLayout* bombs_layout;
    QHBoxLayout* button_size_layout;
    QHBoxLayout* control_buttons_layout;
    QGroupBox* board_size_box;
    QGroupBox* bombs_box;
    QGroupBox* button_size_box;
    QLabel* x_size_label;
    QLabel* y_size_label;
    QComboBox* x_size_combo;
    QComboBox* y_size_combo;
    QSlider* bomb_slider;
    QLabel* bomb_slider_min_percent_label;
    QLabel* bomb_slider_max_percent_label;
    QLabel* bomb_count_label;
    QComboBox* button_size_combo;
    QWidget* control_buttons_widget;
    QPushButton* apply_restart_button;
    QPushButton* apply_later_button;
    QPushButton* cancel_button;

    void setupBoardSize();
    void setupBombs();
    void setupButtonSize();
    void setupControlButtons();
    void readSettings();
    void saveSettings();
};

#endif // SETTINGS_H
