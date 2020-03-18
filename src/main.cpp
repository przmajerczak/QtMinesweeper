#include <QApplication>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

#include "minesweeper.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    int x_size = 20;
    int y_size = 16;
    int bombs_count = x_size * y_size / 5;
    int button_size = 35;

    QFile json_settings("res/settings.json");
    if (json_settings.open(QIODevice::ReadOnly | QIODevice::Text)) {
       QJsonDocument json_doc(QJsonDocument::fromJson(json_settings.readAll()));

       QJsonObject json_obj = json_doc.object();

       x_size = json_obj["x_size"].toInt();
       y_size = json_obj["y_size"].toInt();
       bombs_count = json_obj["bombs_count"].toInt();
       button_size = json_obj["button_size"].toInt();
    }
    json_settings.close();

    //Minesweeper mine(nullptr, x_size, y_size, bombs_count, button_size);
    //mine.show();

    SettingsWindow s(nullptr, x_size, y_size, bombs_count, button_size);
    return s.exec();

    //return a.exec();
}
