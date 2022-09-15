#include "demo.h"
#include "QPainter"
#include "qdebug.h"

Demo::Demo(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

	setPalette(QPalette(Qt::white)); // 设置为白色背景，默认的颜色不是纯白 
	//setAutoFillBackground(true);
	this->resize(400, 400);
}

void Demo::paintEvent(QPaintEvent *event)
{
	//1，绘制一个填充矩形
	//myDrawFilledRect();

	//2，渐变填充
	//myDrawGradient();
	
	//3. 绘制基本图形
	//myDrawShape();

}

void Demo::myDrawFilledRect()
{
	QPainter    painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setRenderHint(QPainter::TextAntialiasing);

	int W = this->width(); 
	int H = this->height(); 
	QRect   rect(W / 4, H / 4, W / 2, H / 2);

	//1 设置画笔
	QPen    pen;
	pen.setWidth(10); //线宽
	pen.setColor(Qt::green); //划线颜色

	//Qt::NoPen,Qt::SolidLine, Qt::DashLine, Qt::DotLine,Qt::DashDotLine,Qt::DashDotDotLine,Qt::CustomDashLine
	pen.setStyle(Qt::SolidLine);//线的类型，实线、虚线等

	//Qt::FlatCap, Qt::SquareCap,Qt::RoundCap
	pen.setCapStyle(Qt::RoundCap);//线端点样式

	//Qt::MiterJoin,Qt::BevelJoin,Qt::RoundJoin,Qt::SvgMiterJoin
	pen.setJoinStyle(Qt::RoundJoin);//线的连接点样式
	painter.setPen(pen);

	//2 设置画刷
	//QPixmap texturePixmap(":/Demo/images/texture.jpg");
	QBrush  brush;
	brush.setColor(Qt::yellow); //画刷颜色
	brush.setStyle(Qt::CrossPattern); //画刷填充样式
    //brush.setStyle(Qt::TexturePattern); //画刷填充样式
    //brush.setTexture(texturePixmap); //设置材质图片
	painter.setBrush(brush);

	//Qt::NoBrush,Qt::SolidPattern,Qt::Dense1Pattern,Qt::Dense2Pattern,..,Qt::Dense7Pattern,Qt::HorPattern
	// Qt::VerPattern, Qt::CrossPattern, Qt::BDiagPattern,Qt::FDiagPattern,Qt::DiagCrossPattern,
	// Qt::LinearGradientPattern,Qt::ConicalGradientPattern,Qt::RadialGradientPattern
	// Qt::TexturePattern


	//3 绘图
	painter.drawLine(rect.left(),rect.top(),rect.right(),rect.bottom());
	//painter.drawRect(rect); 
    //painter.drawRect(this->rect());
    //painter.fillRect(rect,Qt::red);
    //painter.drawRoundRect(rect);
    //painter.drawRoundedRect(rect,40,20);

//    painter.drawEllipse(rect);


	//QPoint points[9] = {
	//	QPoint(5 * W / 12,H / 4),
	//	QPoint(7 * W / 12,H / 4),
	//	QPoint(3 * W / 4,5 * H / 12),
	//	QPoint(3 * W / 4,7 * H / 12),
	//	QPoint(7 * W / 12,3 * H / 4),
	//	QPoint(5 * W / 12,3 * H / 4),
	//	QPoint(W / 4,7 * H / 12),
	//	QPoint(W / 4,5 * H / 12),
	//	QPoint(5 * W / 12,H / 4)
	//};
    //painter.drawPolyline(points,9); // only line,no brush
    //painter.drawPolygon(points,9);  // line and brush 
    //painter.drawPoints(points,9);     // only point,no line ,no brush 


	//qreal   R=100; //半径
	//const   qreal Pi=3.14159;
	//qreal   deg=Pi*72/180;
	//QPoint star_points[5] = {
	//	QPoint(R,0),
	//	QPoint(R*std::cos(deg),-R * std::sin(deg)),
	//	QPoint(R*std::cos(2 * deg),-R * std::sin(2 * deg)),
	//	QPoint(R*std::cos(3 * deg),-R * std::sin(3 * deg)),
	//	QPoint(R*std::cos(4 * deg),-R * std::sin(4 * deg)),
	//};
	//QPainterPath starPath;
	//starPath.moveTo(star_points[0]);
	//starPath.lineTo(star_points[2]);
	//starPath.lineTo(star_points[4]);
	//starPath.lineTo(star_points[1]);
	//starPath.lineTo(star_points[3]);
	//starPath.closeSubpath();
 //   painter.translate(100,300);
 //   painter.drawPath(starPath);
 //   painter.translate(200,0);
 //   painter.drawPath(starPath);
 //   painter.translate(200,0);
 //   painter.drawPath(starPath);

    //painter.drawArc(rect,0*16,110*16); 
    //painter.drawChord(rect,90*16,120*16);
    //painter.drawPie(rect,90*16,120*16);
    //painter.drawText(rect,"Hello, QT");
}

void Demo::myDrawGradient()
{

	QPainter    painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setRenderHint(QPainter::TextAntialiasing);

	int W = this->width(); 
	int H = this->height(); 
	QRect   rect(W / 4, H / 4, W / 2, H / 2);


	 //设置画笔
	QPen    pen;
	pen.setStyle(Qt::DashLine);
	pen.setWidth(10);
	pen.setColor(Qt::red);
	painter.setPen(pen);


	 //线性渐变
    //QLinearGradient  linearGrad(rect.left(),rect.top(),rect.right(),rect.bottom()); //对角线
	QLinearGradient  linearGrad(rect.left(), rect.top(), rect.right(), rect.top());//从左到右
	linearGrad.setColorAt(0, Qt::blue);//起点颜色
	linearGrad.setColorAt(0.5, Qt::green);//中点颜色
	linearGrad.setColorAt(1, Qt::red);//终点颜色
	linearGrad.setSpread(QGradient::ReflectSpread);  //展布模式
	//QGradient::PadSpread ,QGradient::RepeatSpread, QGradient::ReflectSpread
	painter.setBrush(linearGrad);

	//径向渐变
	//QRadialGradient  radialGrad(W/2,H/2,qMax(W/8,H/8),W/2,H/2);
	//// radialGrad.setColorAt(0,Qt::white);
	//radialGrad.setColorAt(0,Qt::green);
	//radialGrad.setColorAt(1,Qt::blue);
	////radialGrad.setSpread(QGradient::ReflectSpread);
	////QGradient::PadSpread ,QGradient::RepeatSpread, QGradient::ReflectSpread
	//painter.setBrush(radialGrad);


	//圆锥型渐变
	//    QConicalGradient  coniGrad(W/2,H/2,45);
	//    coniGrad.setColorAt(0,Qt::yellow);
	//    coniGrad.setColorAt(0.5,Qt::blue);
	//    coniGrad.setColorAt(1,Qt::green);
	////    coniGrad.setSpread(QGradient::PadSpread); //对于锥形渐变不起作用
	//    painter.setBrush(coniGrad);


	//绘图
	painter.drawRect(rect); //只填充定义的渐变区域
	//painter.drawRect(this->rect()); //填充更大区域，会有延展效果

}

void Demo::myDrawShape()
{
	QPainter    painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setRenderHint(QPainter::TextAntialiasing);

	int W = this->width(); 
	int H = this->height(); 

	//设置画笔
	QPen    pen;
	pen.setWidth(10);
	pen.setColor(Qt::black); 
	pen.setStyle(Qt::SolidLine);
	pen.setCapStyle(Qt::FlatCap);
	pen.setJoinStyle(Qt::RoundJoin);
	painter.setPen(pen);

	//1. drawArc() 
	QRect   rect(W/4,H/4,W/2,H/2);
	int startAngle = 0 * 16; //起始0° 
	int spanAngle = 20 * 16;   //旋转20°  大于0 为逆时针
	painter.drawArc(rect, startAngle, spanAngle);

	//2. drawChord()
	//QRect   rect(W/4,H/4,W/2,H/2);
	//int startAngle = 90 * 16; //起始90°
	//int spanAngle = 90 * 16;   //旋转90°
	//painter.drawChord(rect, startAngle, spanAngle);

	//3.drawConvexPolygon()
	//QPoint points[4]={
	//	QPoint(5 * W / 12, H / 4),
	//	QPoint(3 * W / 4, 5 * H / 12),
	//	QPoint(5 * W / 12, 3 * H / 4),
	//	QPoint(2 * W / 4, 5 * H / 12),
	//};
	//painter.drawConvexPolygon(points, 4);


	//4. drawEllipse
	//QRect   rect(W/4,H/4,W/2,H/2);
	//painter.drawEllipse(rect);

	//5. drawImage
	//QRect   rect(W/4,H/4,W/2,H/2);
	//QImage  image(":/Demo/images/qt.jpg");
	//painter.drawImage(rect, image);

	//6.  drawLine
	//QLine   Line(W/4,H/4,W/2,H/2);
	//painter.drawLine(Line);

	//7.  drawLines
	//QRect   rect(W/4,H/4,W/2,H/2);
	//QVector<QLine> Lines;
	//Lines.append(QLine(rect.topLeft(),rect.bottomRight()));
	//Lines.append(QLine(rect.topRight(),rect.bottomLeft()));
	//Lines.append(QLine(rect.topLeft(),rect.bottomLeft()));
	//Lines.append(QLine(rect.topRight(),rect.bottomRight()));
	//painter.drawLines(Lines);

	// 8.QPainterPath
	//QRect   rect(W/4,H/4,W/2,H/2);
	//QPainterPath  path;
	//path.addEllipse(rect);
	//path.addRect(rect);
	//painter.drawPath(path);

	//9.drawPie
	//QRect   rect(W/4,H/4,W/2,H/2);
	//int startAngle = 40 * 16;//起始40°
	//int spanAngle = 120 * 16;//旋转120°
	//painter.drawPie(rect, startAngle, spanAngle);

	//10. drawPixmap
	//QRect   rect(W / 4, H / 4, W / 2, H / 2);
	//QPixmap   pixmap(":/Demo/images/qt.jpg");
	//painter.drawPixmap(rect, pixmap);

	//11. drawPolygon
	//QPoint points[]={
	//    QPoint(5*W/12,H/4),
	//    QPoint(3*W/4,5*H/12),
	//    QPoint(5*W/12,3*H/4),
	//    QPoint(2*W/4,5*H/12),
	//};
	//painter.drawPolygon(points, 4);

	//12.drawPolyline
	//QPoint points[]={
	//    QPoint(5*W/12,H/4),
	//    QPoint(3*W/4,5*H/12),
	//    QPoint(5*W/12,3*H/4),
	//    QPoint(2*W/4,5*H/12)
	//};
	//painter.drawPolyline(points, 4);

	//13.drawRect
	//QRect   rect(W/4,H/4,W/2,H/2);
	//painter.drawRect(rect);

	//14.drawRect
	//QRect   rect(W/4,H/4,W/2,H/2);
	//painter.drawRoundedRect(rect,20,20);

	//14.drawRect
	//QRect   rect(W/4,H/4,W/2,H/2);
	//QFont   font;
	//font.setPointSize(30);
	//font.setBold(true);
	//painter.setFont(font);
	//painter.drawText (rect,"Hello,Qt");

	//.  eraseRect
	//QRect   rect(W/4,H/4,W/2,H/2);
	//painter.eraseRect(rect);

	//15. fillRect
	//QRect   rect(W / 4, H / 4, W / 2, H / 2);
	//painter.fillRect(rect, Qt::green);

	//16.   fillPath
	//QRect  rect(W/4,H/4,W/2,H/2);
	//QPainterPath  path;
	//path.addEllipse(rect);
	//path.addRect(rect);
	//painter.fillPath(path,Qt::red);

	//17.drawPoint
	//painter.drawPoint(QPoint(W/2,H/2));

	//18. drawPoints
	//QPoint points[]={
	//	QPoint(5 * W / 12,H / 4),
	//	QPoint(3 * W / 4,5 * H / 12),
	//	QPoint(2 * W / 4,5 * H / 12)
	//};
	//painter.drawPoints(points, 3);


}

