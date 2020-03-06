#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <iostream>

#include <QRandomGenerator>
#include <QDebug>

#include <mswprbutton.h>
#include "minesweeper.h"
int main(int argc, char *argv[])
{
    /*QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();

    QJsonObject json_obj;
    json_obj["margin"] = 10;
    json_obj["bombs"] = 20;
    json_obj["background_color"] = "grey";

    QJsonDocument json_doc(json_obj);

    QFile jsonfile("config.json");
    jsonfile.open(QFile::WriteOnly);
    jsonfile.write(json_doc.toJson());
    jsonfile.close();

    return 0;*/
    for (int i = 0; i < 10; ++i)
    qDebug() << QRandomGenerator::system()->bounded(0, 20);




            QApplication a(argc, argv);
                MainWindow w;

                MswprButton b(&w, 9,9, false);
                b.setText("hue");
                Minesweeper m(&w, 5, 4, 2);
                w.show();
                return a.exec();
    //return 0;
}
