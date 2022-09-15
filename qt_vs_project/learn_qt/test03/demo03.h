#pragma once

#include <QtWidgets/QWidget>
#include "ui_demo03.h"
#include "qdebug.h"

class Demo03 : public QWidget
{
    Q_OBJECT

public:
    Demo03(QWidget *parent = Q_NULLPTR);

private:
    Ui::Demo03Class ui;

private slots:
	void on_btnCalc_clicked();
	void on_btnDec_clicked();
	void on_btnBin_clicked();
	void on_btnHex_clicked();

};
