#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <iostream>

#include <QRandomGenerator>
#include <QDebug>

#include <QtMath>

#include <mswprbutton.h>
#include "minesweeper.h"

QIcon* MswprButton::checked_icon = new QIcon("checked_icon.svg");

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
/*    MainWindow w;


    w.setCentralWidget(new Minesweeper(&w, 16, 12 , 16*12 / 5));
    w.show();
*/
    Minesweeper mine(nullptr, 15, 10, 30);
    mine.show();




    return a.exec();
    //return 0;
}
