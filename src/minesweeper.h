#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include "progressbar.h"
#include "singlegame.h"
#include "settingswindow.h"

#include <QMainWindow>
#include <QFrame>
#include <QGridLayout>
#include <QLabel>
#include <QSignalMapper>



class Minesweeper : public QMainWindow {

    Q_OBJECT

public:
    Minesweeper(QWidget* parent);
public slots:
    void resetGame();
protected:
#ifndef QT_NO_CONTEXTMENU
    void contextMenuEvent(QContextMenuEvent* event) override;
#endif // QT_NO_CONTEXTMENU
private slots:
    void settingsSlot(void);
    void aboutSlot(void);
private:
    int x_size;
    int y_size;
    int bombs_count;
    int button_size;

    QVBoxLayout* main_layout;
    QWidget* main_widget;
    ProgressBar* progress_bar;
    SingleGame* single_game;
    SettingsWindow* settings;

    QMenu* options_menu;
    QMenu* more_menu;
    QAction* exit_action;
    QAction* settings_action;
    QAction* about_action;
    QAction* restart_action;

    void setupMenuBar();
    void readSettings();




};

#endif // MINESWEEPER_H
