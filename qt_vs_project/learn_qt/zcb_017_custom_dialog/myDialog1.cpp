#include "myDialog1.h"

myDialog1::myDialog1(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
}

myDialog1::~myDialog1()
{


}

int myDialog1::rowCnt()
{
	return ui.spinBox->value();
}

int myDialog1::columnCnt()
{
	return ui.spinBox_2->value();
}

void myDialog1::setSpinDefaultVal(int row, int column)
{
	ui.spinBox->setValue(row);
	ui.spinBox_2->setValue(column);
}

void myDialog1::on_pushButton_clicked()
{
	this->accept();
}

void myDialog1::on_pushButton_2_clicked()
{
	this->reject();
}

