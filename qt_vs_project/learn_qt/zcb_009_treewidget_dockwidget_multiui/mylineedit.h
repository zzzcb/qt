#pragma once

#include <QLineEdit>
#include "ui_mylineedit.h"

class MyLineEdit : public QLineEdit
{
	Q_OBJECT

public:
	MyLineEdit(QWidget *parent = Q_NULLPTR);
	~MyLineEdit();
protected:
	void mouseDoubleClickEvent(QMouseEvent *event);

private:
	Ui::MyLineEdit ui;
};
