#pragma execution_character_set("utf-8")
#include <QtWidgets/QApplication>
#include <QWidget>
#include <QMenu>
#include <QDebug>

class MyWidget1 :public QWidget
{
public:
	MyWidget1(QWidget* parent = nullptr)
		:QWidget(parent)
	{
		setWindowTitle("QWidget右键信号");
		resize(400, 400);

		setContextMenuPolicy(Qt::CustomContextMenu);  // 使用customContextMenuRequested 信号，必须要设置这个policy
		connect(this, &MyWidget1::customContextMenuRequested, this, &MyWidget1::slot_customContextMenuRequested);
	}

private slots :
	void slot_customContextMenuRequested(const QPoint &pos)
	{
		qDebug() << "right mouse press." << pos << " " << mapToGlobal(pos);
	}
};



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	MyWidget1 w;

	w.show();

    return a.exec();
}

