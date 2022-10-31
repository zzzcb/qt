#include <QtWidgets/QApplication>

#include <QWidget>
#include <QLineEdit>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	QWidget w;

	QLineEdit * le1 = new QLineEdit(&w);
	QLineEdit * le2 = new QLineEdit(&w);
	QLineEdit * le3 = new QLineEdit(&w);

	le1->move(50, 50);
	le2->move(100, 100);
	le3->move(150, 150);

	w.setTabOrder(le1, le3);  
	w.setTabOrder(le3, le2);

	w.show();

    return a.exec();
}
