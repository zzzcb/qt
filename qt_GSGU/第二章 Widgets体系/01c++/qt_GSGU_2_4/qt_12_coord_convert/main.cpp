#include <QtWidgets/QApplication>
#include <QWidget>
#include <QMouseEvent>
#include <QDebug>

class ChildWidget :public QWidget
{
public:
	ChildWidget(QWidget*parent = nullptr)
		:QWidget(parent)
	{
		setStyleSheet("background-color:green;");
	}
protected:
	void mousePressEvent(QMouseEvent *event) override
	{
		qDebug() << "self pos is " << event->pos();
		qDebug() << "parent pos is " << mapToParent(event->pos());
		qDebug() << "global pos is " << mapToGlobal(event->pos());
	}
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	QWidget w;
	ChildWidget child(&w);

	w.resize(500, 500);
	child.resize(100, 100);
	child.move(200, 200);

	w.show();

    return a.exec();
}
