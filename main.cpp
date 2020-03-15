#include <QApplication>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>


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

    Minesweeper mine(nullptr, 3, 15, 45/5, 35);
    mine.show();


    return a.exec();
}
