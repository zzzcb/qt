#include <QtWidgets/QApplication>
#include <QWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	QWidget w;
	w.move(300, 300);
	w.resize(500, 500);
	w.show();

    return a.exec();
}
