#pragma once

#include <QPushButton>

class MyButton  : public QPushButton
{
	Q_OBJECT

public:
	MyButton(QWidget *parent=nullptr);
	~MyButton();
};
