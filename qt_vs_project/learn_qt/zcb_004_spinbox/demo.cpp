#include "demo.h"

Demo::Demo(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
}

void Demo::on_btnCalc_clicked()
{
	ui.dSpinBoxTotal->setValue(ui.spinBoxNum->value() * ui.dSpinBoxPrice->value());
}

void Demo::on_btnBin_clicked()
{
	ui.spinBoxDec->setValue(ui.spinBoxBin->value());
	ui.spinBoxHex->setValue(ui.spinBoxBin->value());
}

void Demo::on_btnDec_clicked()
{
	ui.spinBoxBin->setValue(ui.spinBoxDec->value());
	ui.spinBoxHex->setValue(ui.spinBoxDec->value());
}

void Demo::on_btnHex_clicked()
{
	ui.spinBoxDec->setValue(ui.spinBoxHex->value());
	ui.spinBoxBin->setValue(ui.spinBoxHex->value());
}
