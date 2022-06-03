//#include "demo.h"

#include "coloritem.h"
#include "robot.h"

#include <QtWidgets/QApplication>
#include <QGraphicsView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Demo w;
    //w.show();

	QGraphicsScene scene(-200,-200,400,400);

	ColorItem* colorItem;
	for (int i = 0; i < 10; i++)
	{
		colorItem = new ColorItem;
		colorItem->setPos(150*sin(6.28*i/10),150*cos(6.28*i / 10));
		scene.addItem(colorItem);
	}

	Robot* robot = new Robot;
	robot->setPos(0, -20);
	//robot->setTransform(QTransform::fromScale(1.2, 1.2));
	robot->setScale(1.2);
	scene.addItem(robot);

	QGraphicsView view(&scene);
	view.setRenderHint(QPainter::Antialiasing);
	view.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
	view.setBackgroundBrush(QColor(230,200,167));
	view.setWindowTitle("drag and drop robot");
	view.show();

    return a.exec();
}
