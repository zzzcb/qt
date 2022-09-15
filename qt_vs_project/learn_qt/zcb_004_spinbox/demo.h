#pragma once

#include <QtWidgets/QWidget>
#include "ui_demo.h"

class Demo : public QWidget
{
    Q_OBJECT

public:
    Demo(QWidget *parent = Q_NULLPTR);

private:
    Ui::DemoClass ui;

private slots:
	void on_btnCalc_clicked();
	void on_btnBin_clicked();
	void on_btnDec_clicked();
	void on_btnHex_clicked();
};
