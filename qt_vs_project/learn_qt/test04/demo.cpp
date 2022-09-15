#pragma execution_character_set("utf-8")
#include "demo.h"
#include "qdebug.h"

Demo::Demo(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
	qDebug() << "中文";
	qDebug() << "中文啊";

}
