#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_demo.h"
#include "QChartView"
#include "QChart"
using namespace QtCharts;  

class Demo : public QMainWindow
{
    Q_OBJECT

public:
    Demo(QWidget *parent = Q_NULLPTR);

private:
    Ui::DemoClass ui;
	void createChart();
};
