#include "dbmanagerwindow.h"
#include <QApplication>
#include <QRegExp>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DBManagerWindow w;
    w.show();
    
    return a.exec();
}
