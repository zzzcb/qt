#include "mypushbutton.h"

#include <QApplication>
#include <QStylePainter>
#include <QStyleOptionButton>
#include <QDebug>

//  MyPushButton

MyPushButton::MyPushButton(QWidget *parent)
	: QAbstractButton(parent)
{
}

MyPushButton::~MyPushButton()
{
}

QSize MyPushButton::sizeHint() const
{
	QStyleOptionButton option;
	initStyleOption(&option);

	int w = 0, h = 0;

	/** 如果有图标,计算图标的大小 */
	if (!icon().isNull()) 
	{
		int ih = option.iconSize.height();
		int iw = option.iconSize.width() + 4;
		w += iw;
		h = qMax(h, ih);
	}

	/** 计算文本的大小 */
	QString s(text());
	bool empty = s.isEmpty();
	if (empty)
		s = QStringLiteral("XXXX");
	QFontMetrics fm = fontMetrics();
	QSize sz = fm.size(Qt::TextShowMnemonic, s);
	if (!empty || !w)
		w += sz.width();
	if (!empty || !h)
		h = qMax(h, sz.height());
	option.rect.setSize(QSize(w, h));
	
	return style()->sizeFromContents(QStyle::CT_PushButton, &option, QSize(w, h), this);
	//return QSize(w, h);
}

QSize MyPushButton::minimumSizeHint() const
{
	return sizeHint();
}

void MyPushButton::paintEvent(QPaintEvent *e)
{
	QStylePainter painter(this);
	QStyleOptionButton option;

	initStyleOption(&option);

	/** draw */
	painter.drawControl(QStyle::CE_PushButton, option);
}

void MyPushButton::initStyleOption(QStyleOptionButton *option) const
{
	option->initFrom(this);

	/** 状态 */
	if (isDown())
		option->state |= QStyle::State_Sunken;
	else
		option->state |= QStyle::State_Raised;

	/** 文本,图标,图标尺寸 */
	option->text = text();
	option->icon = icon();
	option->iconSize = iconSize();
}

//  MyPushButton2
MyPushButton2::MyPushButton2(QWidget *parent /*= nullptr*/)
	:QPushButton(parent)
{

}

static inline QPainterPath processRect2ChamferPath(QRect rect, qreal xGap = 10, qreal yGap = 10)
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

void MyPushButton2::paintEvent(QPaintEvent *e)
{
	QStyleOptionButton option;
	initStyleOption(&option);

	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	/** 画边框 */
	double xGap = 10;
	painter.drawPath(processRect2ChamferPath(option.rect, xGap));

	/** 画图标 */
	QPixmap pm = option.icon.pixmap(option.iconSize);
	QPoint pmPos = option.rect.topLeft() + QPoint(0, option.rect.height() / 2.) + QPoint(pm.rect().width()/2.+ xGap,0);
	pmPos -= QPoint(pm.rect().width()/2.,pm.rect().height()/2.);
	painter.drawPixmap(pmPos,pm);

	/** 画文字 */
	QFontMetrics fm = QFontMetrics(QApplication::font());
	QPoint textPos = pmPos + QPoint(pm.rect().width(),pm.rect().height()/2.) + QPoint(5, fm.height()/2. - 2);
	painter.drawText(textPos, option.text);
}
