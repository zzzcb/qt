#pragma execution_character_set("utf-8")
#include "demo.h"
#include "qdebug.h"

Demo::Demo(QWidget *parent)
    : QMainWindow(parent)
{
	ui.setupUi(this);
	qDebug() << "QComboBox学习";
	qDebug() << "中文啊";

}
