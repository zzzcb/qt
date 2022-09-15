#pragma execution_character_set("utf-8")
#include "demo.h"
#include "QLineSeries"
#include "qmath.h"
#include "QValueAxis"


Demo::Demo(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	
	createChart();
}

void Demo::createChart()
{
	QChartView *chartView = new QChartView(this); //创建 ChartView
	setCentralWidget(chartView);

	QChart *chart = new QChart(); //创建 Chart
	chart->setTitle("简单函数曲线");
	chartView->setChart(chart);

	//创建 line series
	QLineSeries *series0 = new QLineSeries();
	QLineSeries *series1 = new QLineSeries();
	series0->setName("Sin曲线");
	series1->setName("Cos曲线");
	chart->addSeries(series0); //序列添加到图表
	chart->addSeries(series1);

	//给line series 添加数据
	qreal   t = 0, y1, y2, step = 0.1;
	int cnt = 100;
	for (int i = 0; i < cnt; i++)
	{
		y1 = qSin(t);
		series0->append(t, y1);

		y2 = qCos(t);
		series1->append(t, y2);

		t += step;
	}

	//创建坐标轴
	QValueAxis *axisX = new QValueAxis; //X 轴
	axisX->setRange(0, 10); //设置坐标轴范围
	axisX->setTitleText("time(secs)"); //标题
	//axisX->setLabelFormat("%.1f"); //标签格式
    //axisX->setTickCount(11); //主分隔个数
    //axisX->setMinorTickCount(4);
    //axisX->setGridLineVisible(false);

	QValueAxis *axisY = new QValueAxis; //Y 轴
	axisY->setRange(-2, 2);
	axisY->setTitleText("value");
	//axisY->setLabelFormat("%.2f"); 
	//axisY->setTickCount(5);
	//axisY->setMinorTickCount(4);
	//axisY->setGridLineVisible(false);

	chart->setAxisX(axisX, series0); // 为series 设置坐标轴 
	chart->setAxisY(axisY, series0);

	chart->setAxisX(axisX, series1); 
	chart->setAxisY(axisY, series1);

}
