#include "mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //setFixedSize(640, 480);
    menuBar = new QMenuBar(this);
    setMenuBar(menuBar);

    /*main_widget = new QWidget(this);
    main_widget->setStyleSheet("QWidget {background-color:dimgray;}");
    mainer_layout = new QBoxLayout(QBoxLayout::TopToBottom, main_widget);
    main_widget->setLayout(mainer_layout);
    setCentralWidget(main_widget);*/
}

MainWindow::~MainWindow()
{

}

