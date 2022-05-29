#include "demo.h"
#include "graphwidget.h"
#include <QtWidgets/QApplication>
#include <QMainWindow>
#include <QGridLayout>

#include <iostream>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	
	//Demo w;
	//w.show();



	QMainWindow w;
	QWidget* centerWidget = new QWidget(&w);

	QGridLayout* layout = new QGridLayout(centerWidget);
	//layout->setMargin(0);

	GraphWidget *graphWidget = new GraphWidget(centerWidget);
	layout->addWidget(graphWidget, 0, 0, 1, 1 );

	w.setCentralWidget(centerWidget);
	w.show();

    return a.exec();

}
