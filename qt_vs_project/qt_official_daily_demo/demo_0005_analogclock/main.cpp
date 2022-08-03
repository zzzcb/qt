#include <QGuiApplication>

#include "rasterwindow.h"
#include <QDebug>
#include <QPainter>
#include <QTime>

class AnalogClockWindow :public RasterWindow
{
public:
	AnalogClockWindow();

protected:
	void render(QPainter *painter) override;
	void timerEvent(QTimerEvent *event) override;

private:
	int mn_timerId;
};

AnalogClockWindow::AnalogClockWindow()
{
	setTitle("Analog Clock");
	resize(200, 200);

	mn_timerId = startTimer(1000);
}



void AnalogClockWindow::render(QPainter *p)
{
	static const QPoint hourHand[3] = {
		QPoint(7, 8),
		QPoint(-7, 8),
		QPoint(0, -40)
	};
	static const QPoint minuteHand[3] = {
		QPoint(5, 8),
		QPoint(-5, 8),
		QPoint(0, -70)
	};
	static const QPoint secondHand[3] = {
		QPoint(3, 8),
		QPoint(-3, 8),
		QPoint(0, -90)
	};

	QColor hourColor(127, 0, 127);
	QColor minuteColor(0, 127, 127, 191);
	QColor secondColor(127, 127, 0);

	// 抗锯齿
	p->setRenderHint(QPainter::Antialiasing);
	// 画笔移动到中心
	p->translate(width() / 2, height() / 2);

	// 选取小边作为边长,表是正方形的
	int side = qMin(width(), height());
	
	// 缩放画笔 !!!
	p->scale(side / 200.0, side / 200.0);

	p->setPen(Qt::NoPen);
	p->setBrush(hourColor);

	// qtime 获取当前时间
	QTime time = QTime::currentTime();
	p->save();  // 绘制前save下
	// 绘制 时针
	p->rotate(30.0 * ((time.hour() + time.minute() / 60.0 + time.second()/3600.0)));
	p->drawConvexPolygon(hourHand, 3);
	p->restore();
	// 绘制 时针刻度
	p->setPen(hourColor);
	for (int i = 0; i < 12; ++i) {
		p->drawLine(84, 0, 96, 0);
		p->rotate(30.0);
	}

	// 绘制分针
	p->setPen(Qt::NoPen);
	p->setBrush(minuteColor);
	p->save();
	p->rotate(6.0 * (time.minute() + time.second() / 60.0));
	p->drawConvexPolygon(minuteHand, 3);
	p->restore();
	// 绘制分针刻度
	p->setPen(minuteColor);
	for (int j = 0; j < 60; ++j) 
	{
		if ((j % 5) != 0) // 此处是 时针刻度 跳过
			p->drawLine(88, 0, 96, 0);
		p->rotate(6.0);
	}

	// 绘制秒针
	p->setPen(Qt::NoPen);
	p->setBrush(secondColor);
	p->save();
	p->rotate(6.0 * time.second());
	p->drawConvexPolygon(secondHand, 3);
	p->restore();

	// 绘制 中心一个点 
	p->save();
	p->setBrush(Qt::black);
	p->drawEllipse(-3, -3, 6, 6);
	p->restore();
}

void AnalogClockWindow::timerEvent(QTimerEvent *event)
{
	if (event->timerId() == mn_timerId)
	{
		renderLater();  // raster window 中的函数(父类)
	}
}

int main(int argc, char *argv[])
{
	QGuiApplication a(argc, argv);

	AnalogClockWindow w;
	w.show();


    return a.exec();
}
