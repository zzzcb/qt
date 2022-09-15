#include "demo.h"
#include "qdebug.h"

Demo::Demo(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

	setMouseTracking(true);
	setAutoFillBackground(true);
}

void Demo::mouseReleaseEvent(QMouseEvent *event)
{
	qDebug() << "mouse release ... ";

	QWidget::mouseReleaseEvent(event);  
}
