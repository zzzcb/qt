#pragma execution_character_set("utf-8")
#include <QtWidgets/QApplication>
#include <QMainWindow>
#include <QStatusBar>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	QMainWindow w;
	w.setStatusBar(new QStatusBar(&w));

	w.setStatusTip("显示在状态栏");
	w.setToolTip("工具提示,简单有力");
	w.setWhatsThis("这是啥提示,它通常比toolTip更长更详细,默认shift+f1触发");
	w.show();
	
    return a.exec();
}
