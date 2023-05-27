#include "mystyle.h"
#include <QtWidgets>
#include <QDebug>
MyStyle::MyStyle() 
	:QProxyStyle(QStyleFactory::create("windows"))
{
	qDebug() << QStyleFactory::keys();
}

void MyStyle::drawPrimitive(PrimitiveElement element,
                                       const QStyleOption *option,
                                       QPainter *painter,
                                       const QWidget *widget) const
{
    switch (element) {
		case PE_PanelButtonCommand:
		{
			QPainterPath borderPath = processRect2ChamferPath(option->rect);
			QPainterPath contentPath = processRect2ChamferPath(option->rect.adjusted(1, 1, -1, -1));

			QBrush brush;
			/** 如果按钮被按下或选中 */
			if (option->state & (State_Sunken | State_On))
				brush = option->palette.mid();
			else
				brush = option->palette.button();

			painter->save();
			painter->setRenderHint(QPainter::Antialiasing, true);
			painter->drawPath(borderPath);
			painter->fillPath(contentPath,brush);
			painter->restore();
		}
        break;
    default:
        QProxyStyle::drawPrimitive(element, option, painter, widget);
    }
}

QPainterPath MyStyle::processRect2ChamferPath(const QRect& rect, qreal xGap /*= 10*/, qreal yGap /*= 10*/)
{
	int x = rect.x();
	int y = rect.y();
	int w = rect.width();
	int h = rect.height();

	QVector<QPointF> vPoint;
	vPoint << QPointF(x + xGap, y)
		<< QPointF(x + w, y)
		<< QPointF(x + w, y + h - yGap)
		<< QPointF(x + w - xGap, y + h)
		<< QPointF(x, y + h)
		<< QPointF(x, y + yGap)
		<< QPointF(x + xGap, y);

	QPainterPath path(vPoint.first());
	for (auto & pt : vPoint)
		path.lineTo(pt);

	return path;
}
