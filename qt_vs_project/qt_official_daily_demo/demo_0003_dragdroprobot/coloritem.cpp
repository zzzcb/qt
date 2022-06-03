#include "coloritem.h"

#include <QRandomGenerator>
#include <QPainter>
#include <QCursor>
#include <QGraphicsSceneEvent>
#include <QApplication>
#include <QDrag>
#include <QWidget>
#include <QMimeData>
#include <QPixmap>
#include <QBitmap>

#include <QDebug>

ColorItem::ColorItem()
	:mColor(QColor(QRandomGenerator::global()->bounded(256), QRandomGenerator::global()->bounded(256), QRandomGenerator::global()->bounded(256)))
{
	
	setToolTip(QString("color rgb is %1,%2,%3\n%4").arg(mColor.red()).arg(mColor.green()).arg(mColor.blue()).arg("Click and drag this color to the robot!"));
	setCursor(Qt::OpenHandCursor);
	setAcceptedMouseButtons(Qt::LeftButton);
}

ColorItem::~ColorItem()
{
}

void ColorItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = nullptr */)
{
	// draw shadow 
	painter->setPen(Qt::NoPen);
	painter->setBrush(Qt::darkGray);
	painter->drawEllipse(-12, -12, 30, 30);

	// draw itself 
	painter->setPen(Qt::black);
	painter->setBrush(QBrush(mColor));
	painter->drawEllipse(-15, -15, 30, 30);

}

QRectF ColorItem::boundingRect() const
{
	return QRectF(-15.5, -15.5, 31, 31);
}

void ColorItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	setCursor(Qt::ClosedHandCursor);
}

void ColorItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	//qDebug() <<"---->"<< event->screenPos();
	//qDebug() << "-->" << event->buttonDownScreenPos(Qt::LeftButton);
	if (QLineF(event->screenPos(),event->buttonDownScreenPos(Qt::LeftButton)).length() < QApplication::startDragDistance())
		return;

	QDrag * drag = new QDrag(event->widget());
	
	//mime for trans using drag and drop
	QMimeData* mime = new QMimeData;

	static int n = 0;
	if (n++ > 2 && QRandomGenerator::global()->bounded(3) == 0)
	//if(1)
	{
		// set pixmap to drag 
		QImage img(":/images/head.png");
		drag->setPixmap(QPixmap::fromImage(img).scaled(30,40)); 

	    //set mime to drag 
		mime->setImageData(img);
		drag->setMimeData(mime);

		// set hot spot to drag 
		drag->setHotSpot(QPoint(15, 30));
	}
	else
	{
		// set mime to drag 
		mime->setColorData(mColor);
		mime->setText(QString("#%1%2%3")
			.arg(mColor.red(), 2, 16, QLatin1Char('0'))
			.arg(mColor.green(), 2, 16, QLatin1Char('0'))
			.arg(mColor.blue(), 2, 16, QLatin1Char('0')));
		drag->setMimeData(mime);


		// set pixmap to drag 
		QPixmap pixmap(34, 34);
		pixmap.fill(Qt::white);

		QPainter painter(&pixmap);
		painter.translate(15, 15);
		painter.setRenderHint(QPainter::Antialiasing);
		paint(&painter, 0, 0);
		painter.end();
		pixmap.setMask(pixmap.createHeuristicMask());
		drag->setPixmap(pixmap);
			
		// set hot spot to drag 
		drag->setHotSpot(QPoint(15, 20));
	}

	drag->exec();
	setCursor(Qt::OpenHandCursor);
}

void ColorItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	setCursor(Qt::OpenHandCursor);
}
