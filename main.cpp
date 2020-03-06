#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();/*

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
}