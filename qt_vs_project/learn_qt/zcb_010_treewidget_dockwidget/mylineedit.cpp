#pragma execution_character_set("utf-8")
#include "mylineedit.h"

MyLineEdit::MyLineEdit(QWidget *parent)
	: QLineEdit(parent)
{
	connect(this, &QLineEdit::returnPressed, this, &MyLineEdit::on_lineEdit_returnPressed);
}

MyLineEdit::~MyLineEdit()
{
}

void MyLineEdit::mouseDoubleClickEvent(QMouseEvent *event)
{
	QString s = QFileDialog::getExistingDirectory();
	if (s.isEmpty())
		s = "C:/Users/admin/Desktop";

	this->setText(s);
	emit chooseDirCompleted();
}

void MyLineEdit::on_lineEdit_returnPressed()
{
	QFileInfo fInfo(this->text());
	if (!fInfo.exists())
	{
		qDebug() << "路径不对,将使用桌面" << this->text();
		this->setText("C:/Users/admin/Desktop");

	}

	if (!fInfo.isDir())
	{
		qDebug() << "路径不对,将使用桌面" << this->text();
		this->setText("C:/Users/admin/Desktop");
	}

	emit chooseDirCompleted();
}
