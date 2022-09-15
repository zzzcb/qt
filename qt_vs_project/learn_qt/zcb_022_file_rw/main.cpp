#include "demo.h"
#include <QtWidgets/QApplication>

/*
这里主要使用了QFile(io device) 和 QTextStream两个类来操作文本文件的读写
*/
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Demo w;
    w.show();
    return a.exec();
}
