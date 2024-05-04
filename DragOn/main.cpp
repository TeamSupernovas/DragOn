
#include <QtCore>
#include <QApplication>

#include "DragOnMainWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DragOnMainWindow w;
    w.showMaximized();
    w.show();
    return a.exec();
}
