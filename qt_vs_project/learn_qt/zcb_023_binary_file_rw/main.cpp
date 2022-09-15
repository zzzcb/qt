#include "demo.h"
#include <QtWidgets/QApplication>

/*
这里主要使用了QFile(io device) 和 QDataStream 两个类来操作二进制文件的读写(序列化 与 反序列化)
stm 不是标准的 二进制格式
dat 是完全的二进制格式 它的大小会更小些 
*/
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Demo w;
    w.show();
    return a.exec();
}
