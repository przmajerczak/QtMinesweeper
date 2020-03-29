#include <QApplication>

#include "minesweeper.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Minesweeper mine(nullptr);
    mine.show();

    return a.exec();
}
