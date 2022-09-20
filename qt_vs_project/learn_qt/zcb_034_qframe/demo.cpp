#include "demo.h"

#include <QLabel>
#include <QProgressBar>
#include <QKeyEvent>
#include <QPainter>
#include <QDebug>


Demo::Demo(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

	QLabel* label = new QLabel("TEST", this);
	label->setFrameStyle(QFrame::Panel | QFrame::Plain);
	label->setLineWidth(4);
	label->setMidLineWidth(3); // not work 
	label->move(100, 100);
	qDebug() << "--------------> frame width " << label->frameWidth();  // 4 

	QLabel* label2 = new QLabel("TEST", this);
	label2->setFrameStyle(QFrame::Box | QFrame::Plain);
	label2->setLineWidth(4);   
	label2->setMidLineWidth(3);// not work 
	label2->move(300, 100);
	qDebug() << "--------------> frame width " << label2->frameWidth();  // 4

	QLabel* label3 = new QLabel("TEST", this);
	label3->setFrameStyle(QFrame::Box | QFrame::Raised);
	label3->setLineWidth(4);   
	label3->setMidLineWidth(3);// work 
	label3->move(500, 100);
	qDebug() << "--------------> frame width " << label3->frameWidth();  // 11


	QLabel* label4 = new QLabel("TESTasdfjsdlfkjdslfj", this);
	label4->setFrameStyle(QFrame::Panel | QFrame::Plain);
	label4->setLineWidth(3);  
	label4->move(100, 300);


	QLabel* label5 = new QLabel("TESTasdfjsdlfkjdslfj", this);
	label5->setFrameStyle(QFrame::Panel | QFrame::Plain);
	label5->setContentsMargins(20, 0, 20, 0); // widget - frame 
	label5->move(300, 300);


	m_pLabel6 = new QLabel("TESTasdfjsdlfkjdslfj", this);
	m_pLabel6->setFrameStyle(QFrame::Panel | QFrame::Plain);
	m_pLabel6->setMargin(5);					//  frame - content 
	m_pLabel6->move(500, 300);

	label4->setAutoFillBackground(true);  // setAutoFillBackground
	m_pLabel6->setAttribute(Qt::WA_OpaquePaintEvent); 


}

Demo::~Demo()
{



}

void Demo::mousePressEvent(QMouseEvent *event)
{
	qDebug()<< m_pLabel6->underMouse();

	qDebug() << "winId " << winId();

}

void Demo::keyPressEvent(QKeyEvent *event)
{
	qDebug() << "event ........  " << event->key();
}

void Demo::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.drawPixmap(rect(),QPixmap(":/propagation-custom.png"));

}

