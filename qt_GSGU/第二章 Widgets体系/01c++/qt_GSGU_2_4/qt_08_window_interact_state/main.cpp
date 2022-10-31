#pragma execution_character_set("utf-8")
#include <QtWidgets/QApplication>
#include <QWidget>

int main1(int argc, char *argv[])
{
    QApplication a(argc, argv);

	QWidget w;
	//w.setWindowModified(true);
	w.setWindowTitle("我不是Qt[*]");
	w.show();

    return a.exec();
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QWidget w;
	QWidget w2;
	w2.show();
	w.show();

	w2.raise();
	qDebug() << w.isActiveWindow(); // true
	qDebug() << w2.isActiveWindow(); // false

	return a.exec();
}

