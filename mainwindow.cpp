#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setFixedSize(640, 480);
    menuBar = new QMenuBar(this);
    setMenuBar(menuBar);
}

MainWindow::~MainWindow()
{

}

