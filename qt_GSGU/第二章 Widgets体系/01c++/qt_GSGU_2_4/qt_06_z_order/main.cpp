#include <QtWidgets/QApplication>
#include <QWidget>

int main1(int argc, char *argv[])
{
    QApplication a(argc, argv);

	QWidget w;
	QWidget w1(&w);
	QWidget w2(&w);
	QWidget w3(&w);
	w.resize(300, 300);
	w1.resize(100, 100);
	w2.resize(100, 100);
	w3.resize(100, 100);
	
	w2.move(30, 30);
	w3.move(60, 60);
	
	w1.setStyleSheet("background-color:red");
	w2.setStyleSheet("background-color:green");
	w3.setStyleSheet("background-color:blue");

	//w1.raise();
	//w3.lower();
	//w3.stackUnder(&w1);

	w.show();
  
    return a.exec();
}


/**
	点击哪个,哪个到最顶层
*/
class MyWidget :public QWidget 
{
public:
	MyWidget(QWidget*parent = nullptr)
		:QWidget(parent)
	{
		resize(100, 100);
	}
protected:
	void mousePressEvent(QMouseEvent *event) override
	{
		raise();
	}
};

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QWidget w;
	MyWidget w1(&w);
	MyWidget w2(&w);
	MyWidget w3(&w);
	w.resize(300, 300);
	w1.resize(100, 100);
	w2.resize(100, 100);
	w3.resize(100, 100);

	w2.move(30, 30);
	w3.move(60, 60);

	w1.setStyleSheet("background-color:red");
	w2.setStyleSheet("background-color:green");
	w3.setStyleSheet("background-color:blue");

	w.show();

	return a.exec();
}


