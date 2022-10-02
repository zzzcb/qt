#include "mybutton.h"

#include <QDebug>

MyButton::MyButton(QWidget *parent/*=nullptr*/)
	:QPushButton(parent)
{
}

MyButton::~MyButton()
{
	qDebug() << "---------> " << text() << " pointer addr " << this;
}
