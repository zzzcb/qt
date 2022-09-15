#include "demo.h"
#include <QtWidgets/QApplication>

/*
  QPainter 视口 viewpoint 和 窗口 window 
*/
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Demo w;
    w.show();
    return a.exec();
}
