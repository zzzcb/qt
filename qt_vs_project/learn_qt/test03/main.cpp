#include "demo03.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Demo03 w;
    w.show();
    return a.exec();
}
