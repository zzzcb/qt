#pragma execution_character_set("utf-8")
#include "splashscreen.h"

#include <QPainter>
#include <QThread>

SplashScreen::SplashScreen(QPixmap pixmap /*= QPixmap()*/, QWidget *parent /*= nullptr*/)
	:QSplashScreen(parent)
{
	setPixmap(pixmap);
	setAutoFillBackground(false);
	setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
	
	m_tTextColor = Qt::black;
	m_tRect = pixmap.rect().adjusted(5, 5, -5, -5);
}

SplashScreen::~SplashScreen()
{
}

void SplashScreen::testThis()
{
	// 1,构造splash
	QPixmap pixmap(":/images/orange_splash_screen.png");
	SplashScreen splash(pixmap);

	// 2,设置字体 font and palette 
	splash.setFont(QFont("Microsoft YaHei", 10));

	// 3,同步调用 setProgress 和 showMessage 
	for (int i = 0; i < 100; i++)
	{
		splash.setProgress(i);
		splash.showMessage("loading... | 插件 " + QString::number(i));
		splash.show();

		QThread::msleep(100);
	}
}

void SplashScreen::setProgress(double percent,int barHeight)
{
	m_dPercent = percent;
	m_dBarHeight = barHeight;
}

void SplashScreen::showMessage(const QString &message, int alignment, const QColor &color)
{
	m_strMsg = message;
	m_tTextColor = color;
	m_nTextAlign = alignment;
	QSplashScreen::showMessage(message, alignment, color);
}

void SplashScreen::drawContents(QPainter *painter)
{
	if (!m_tRect.isValid())
		return;

	painter->save();

	// draw message 
	painter->setPen(m_tTextColor);
	painter->setFont(font());
	painter->drawText(m_tRect, m_nTextAlign, m_strMsg);
	// draw progress bar 
	QPoint leftUp = m_tRect.bottomLeft() + QPoint(10, -m_dBarHeight);
	QPoint rightDown = m_tRect.bottomRight() + QPoint(-10, -m_dBarHeight) + QPoint(0, m_dBarHeight);
	//painter->drawRect(QRect(leftUp, rightDown));
	QPoint dynamicRightDown(rightDown.x()*m_dPercent / 100., rightDown.y());
	painter->fillRect(QRect(leftUp, dynamicRightDown).adjusted(1, 1, -1, 0),QGradient::FreshOasis);

	painter->restore();
	
	// =========

	painter->save();

	// draw percent text 
	QFont ft = font();
	ft.setPixelSize(m_dBarHeight);
	painter->setFont(ft);
	QPoint textPt((leftUp + rightDown) / 2. + QPoint(0, m_dBarHeight / 2.));
	painter->drawText(textPt, QString::number(m_dPercent) + " %");
	
	painter->restore();
}
