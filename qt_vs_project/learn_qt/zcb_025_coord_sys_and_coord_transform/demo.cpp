#include "demo.h"
#include "QPainter"
#include "qdebug.h"

Demo::Demo(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
	setPalette(QPalette(Qt::white));

	resize(600, 600);
}

void Demo::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setRenderHint(QPainter::TextAntialiasing);

	//生成五角星的5个顶点的
	qreal R = 100;
	QPolygonF starPolygon;
	starPolygon << QPointF(2*R, R);
	for (int i = 1; i < 5; ++i)
		starPolygon << QPointF(R + R * std::cos(1.2 * i * 3.14),
			R + R * std::sin(1.2 * i * 3.14));

	// 在中心( 100 100) 画一个 R = 100 的五角星  
	painter.save();
	QPointF center(100, 100);
	QPointF rVec(100, 100);
	painter.translate(center - rVec);
	painter.drawPolygon(starPolygon);
	painter.restore();

	// 在中心( 300 100) 画一个 R = 50 的五角星  
	painter.save();
	center = QPointF(300, 100);
	rVec = QPointF(50, 50);
	painter.translate(center - rVec);
	painter.scale(0.5, 0.5);
	painter.drawPolygon(starPolygon);
	painter.restore();

	// 在中心( 450 100) 画一个 R = 100 的五角星  
	// 旋转的话 需要注意 系统默认是以左上角旋转的,比较麻烦一些 
	painter.save();
	float w = 2*R;
	float h = 2*R;
	float alpha = atan2(h,w);          // 均为弧度 
	float theta = 90*3.1415926/180.0;
	float r = std::sqrt(1.0 / 4.0*(h*h + w * w)); 
	float xc = (450 - R)+ 1 / 2.*w;
	float yc = (100 - R) + 1 / 2.*h;
	float xDes = -r * std::cos(theta)*std::cos(alpha) + r * std::sin(theta)*std::sin(alpha) + xc;
	float yDes = -r * std::cos(theta)*std::sin(alpha) - r * std::sin(theta)*std::cos(alpha) + yc;
	painter.translate(xDes, yDes);
	painter.rotate(theta * 180 / 3.1415926);
	painter.drawPolygon(starPolygon);
	painter.restore();

}

