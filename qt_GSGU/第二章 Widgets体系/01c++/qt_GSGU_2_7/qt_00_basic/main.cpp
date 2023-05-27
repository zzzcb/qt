#pragma execution_character_set("utf-8")

#include "mypushbutton.h"
#include "mystyle.h"

#include <QApplication>

#include <QCheckBox>
#include <QPushButton>
#include <QCommandLinkButton>
#include <QRadioButton>
#include <QToolButton>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	a.setStyle(new MyStyle);

	QIcon icon("../images/love.png");

	QWidget mw;
	/** QCheckBox */
	QCheckBox* ck = new QCheckBox(&mw);
	ck->setText("已阅读上述协议,并同意条款");
	ck->setTristate(true);
	ck->move(10, 10);

	/** QPushButton */
	QPushButton* btn = new QPushButton("QPushButton",&mw);
	btn->setIcon(icon);
	btn->move(50, 50);

	MyPushButton* myBtn = new MyPushButton(&mw);
	myBtn->setIcon(icon);
	myBtn->setText("MyButton");
	myBtn->move(100, 100);

	MyPushButton2* myBtn2 = new MyPushButton2(&mw);
	myBtn2->setIcon(icon);
	myBtn2->setText("MyButton2");
	myBtn2->move(150, 150);

	/** QCommandLinkButton */
	QCommandLinkButton* cmdLinkBtn = new QCommandLinkButton("text","description",&mw);
	cmdLinkBtn->move(200, 200);

	/** QRadioButton */
	QRadioButton* radioBtn = new QRadioButton("text", &mw);
	QRadioButton* radioBtn2 = new QRadioButton("text2", &mw);
	radioBtn->move(250, 250);
	radioBtn2->move(250, 270);

	/** QToolButton */
	QToolButton* toolBtn = new QToolButton(&mw);
	toolBtn->setIcon(icon);
	toolBtn->move(300, 300);
	QToolButton* toolBtn2 = new QToolButton(&mw);
	toolBtn2->setIcon(icon);
	toolBtn2->setText("ToolBtn2");
	toolBtn2->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	toolBtn2->move(350, 300);


	mw.show();
	 
    return a.exec();
}

