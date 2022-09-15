#include "demo.h"
#include <QtWidgets/QApplication>
#include <QObject>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Demo w;

	QPushButton * btn = new QPushButton("click me",&w);
	btn->move(100, 100);
	QObject::connect(btn, &QPushButton::clicked, [&]() {
		QMenu* menu= w.createPopupMenu();
		if (menu)
		{
			menu->exec(QPoint(300,300));
		}
		delete menu;
	});

	w.show();



    return a.exec();
}





