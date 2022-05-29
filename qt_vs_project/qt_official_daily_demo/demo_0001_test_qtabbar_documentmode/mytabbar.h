#pragma once

#include <QWidget>
#include "ui_mytabbar.h"

#include <QGridLayout>
#include <QTabBar>
#include <QFrame>
#include <QVBoxLayout>
#include <QLabel>

class MyTabbar : public QWidget
{
	Q_OBJECT

public:
	MyTabbar(QWidget *parent = Q_NULLPTR);
	~MyTabbar();

private:
	QGridLayout* mpGridLayout;
	QFrame* mpFrame1;
	QFrame* mpFrame2;
	QVBoxLayout* mpVInnerLayout1;
	QVBoxLayout* mpVInnerLayout2;
	QTabBar* mpTabBar1;
	QTabBar* mpTabBar2;

	QLabel* mpLabel1;
	QLabel* mpLabel2;
};
