#include "demo.h"
#include <QtWidgets/QApplication>

/*
该项目使用的是QDesigner 自定义控件  每次修改都需要重新编译为dll 不好用
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Demo w;
    w.show();
    return a.exec();
}
