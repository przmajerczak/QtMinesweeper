#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <iostream>

#include <QRandomGenerator>
#include <QDebug>
#include <QListIterator>

#include <mswprbutton.h>
#include "minesweeper.h"
int main(int argc, char *argv[])
{
    /*

    QJsonObject json_obj;
    json_obj["margin"] = 10;
    json_obj["bombs"] = 20;
    json_obj["background_color"] = "grey";

    QJsonDocument json_doc(json_obj);

    QFile jsonfile("config.json");
    jsonfile.open(QFile::WriteOnly);
    jsonfile.write(json_doc.toJson());
    jsonfile.close();

*/



    QApplication a(argc, argv);
    MainWindow w;

    auto minesweeper = new Minesweeper(&w, 20, 20, 40);

    w.main_layout->addWidget(minesweeper);
    w.main_layout->setAlignment(minesweeper, Qt::AlignCenter);
    w.show();




    return a.exec();
    //return 0;
}
