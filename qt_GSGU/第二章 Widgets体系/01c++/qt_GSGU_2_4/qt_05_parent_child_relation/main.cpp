#include <QtWidgets/QApplication>
#include <QWidget>
#include <QLabel>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	QWidget w;
	w.resize(500, 500);
	QLabel lb1("label1",&w);
	qDebug() << w.childAt(0, 0);   // QLabel(0x572beff548)
	qDebug() << w.childAt(100, 0); // QWidget(0x0)

	qDebug() << lb1.parentWidget(); 
	qDebug() << lb1.parent();

	QLabel lb2("label2", &w);
	lb2.move(10, 80);
	qDebug() << w.childrenRect();

	w.show();

    return a.exec();
}

