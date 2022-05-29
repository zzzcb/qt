#include "mytabbar.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyTabbar w;
    w.show();
    return a.exec();
}
