#include "zzzwidget.h"
#include "qdebug.h"

ZZZWidget::ZZZWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

ZZZWidget::~ZZZWidget()
{
}

void ZZZWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
	qDebug() << "hello";

}
