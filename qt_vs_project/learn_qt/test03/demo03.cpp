#include "demo03.h"

Demo03::Demo03(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
}

void Demo03::on_btnCalc_clicked()
{
	double total = ui.editNum->text().toInt()*ui.editPrice->text().toDouble();
	QString s;
	s.setNum(total, 'f', 2);
	ui.editTotal->setText(s);
	qDebug() << "中文在这";
	qDebug() << "中文在这啊";
}

void Demo03::on_btnDec_clicked()
{
	int val = ui.editDec->text().toInt(); 
	
	QString s;
	s.setNum(val, 2); 
	ui.editBin->setText(s);
	s.setNum(val, 16);
	ui.editHex->setText(s);
}
void Demo03::on_btnBin_clicked()
{
	bool ok;
	int val = ui.editBin->text().toInt(&ok, 2);

	QString s;
	s.setNum(val, 10);
	ui.editDec->setText(s);

	s.setNum(val, 16);
	ui.editHex->setText(s);
}
void Demo03::on_btnHex_clicked()
{
	bool ok;
	int val = ui.editHex->text().toInt(&ok, 16);

	QString s;
	s.setNum(val, 2);
	ui.editBin->setText(s);

	s.setNum(val, 10);
	ui.editDec->setText(s);
}
