#include "demo.h"

Demo::Demo(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	xgx = new XGXLib::XGX(ui.centralWidget);
}

// slot 
void Demo::on_pushButton_clicked()
{
	xgx->AboutBox();
}

