#include "demo.h"
#include <QtWidgets/QApplication>
#include <QComboBox>
#include <QStyleFactory>
#include <QDebug>

int main(int argc, char *argv[])
{
	qDebug() << QStyleFactory::keys();  // ("windowsvista", "Windows", "Fusion")  可以通过命令行参数 -style设置
    QApplication a(argc, argv);
	a.setStyle("Fusion");
	qDebug() << "-------->当前电脑所有可用style " << a.style();
	Demo w;
	QComboBox* box = new QComboBox(&w);
    w.show();
    return a.exec();
}
