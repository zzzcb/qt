/**
代码参考:https://blog.csdn.net/hitzsf/article/details/108847841
*/
#include "demo.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Demo w;
    w.show();
    return a.exec();
}


/**
output
"hello qt!"
"hello qt!"
"我从哪里来?"
"我要到哪里去?"
-------------------
"hello qt!"
"hello qt!"
"我从哪里来?"
"我要到哪里去?"
*/