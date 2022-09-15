#pragma once

#include <QDialog>
#include "ui_myDialog1.h"

class myDialog1 : public QDialog
{
	Q_OBJECT

public:
	myDialog1(QWidget *parent = Q_NULLPTR);
	~myDialog1();

	int rowCnt();
	int columnCnt();
	void setSpinDefaultVal(int row,int column);

private:
	Ui::myDialog1 ui;
private slots:
	void on_pushButton_clicked();
	void on_pushButton_2_clicked();
};
