#include "demo.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Demo w;
    w.show();
    return a.exec();
}
