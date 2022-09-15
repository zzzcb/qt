#include "mylineedit.h"
#include "qdebug.h"

MyLineEdit::MyLineEdit(QWidget *parent)
	: QLineEdit(parent)
{
	ui.setupUi(this);
}

MyLineEdit::~MyLineEdit()
{
}

void MyLineEdit::mouseDoubleClickEvent(QMouseEvent *event)
{
	qDebug() << "hello";
}
