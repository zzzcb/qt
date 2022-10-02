#include <QApplication>

/**========================»æ»­°å1==============================*/
//#include "mydrawboard.h"
//
//int main(int argc,char** argv)
//{
//	QApplication app(argc, argv);
//
//	MyDrawboard myDrawBoard;
//	myDrawBoard.show();
//
//	return app.exec();
//}

/**========================»æ»­°å2==============================*/
//#include "mydrawboard2.h"
//
//#include <QObject>
//#include <QDebug>
//
//class AppFilter :public QObject
//{
//	QOBJECT_H
//public:
//	AppFilter(QString id,QObject*parent =nullptr)
//		:m_strId(id)
//	{}
//
//	bool eventFilter(QObject *watched, QEvent *event) override;
//private:
//	QString m_strId;
//};
//
//bool AppFilter::eventFilter(QObject *watched, QEvent *event)
//{
//
//	if (event->type() == QEvent::MouseButtonPress)
//	{
//		qDebug() << "watched obj addr " << watched << " id " << m_strId;
//		return false;
//	}
//
//	return QObject::eventFilter(watched, event);
//}
//
//class ReceiverFilter :public QObject
//{
//	QOBJECT_H
//public:
//	ReceiverFilter(QString id, QObject*parent = nullptr)
//		:m_strId(id)
//	{}
//
//	bool eventFilter(QObject *watched, QEvent *event) override;
//private:
//	QString m_strId;
//};
//bool ReceiverFilter::eventFilter(QObject *watched, QEvent *event)
//{
//	if (event->type() == QEvent::MouseButtonPress)
//	{
//		qDebug() << "watched obj addr " << watched << " id " << m_strId;
//		//if (m_strId == "receiver filter2")
//		//	return false;
//	}
//
//	return QObject::eventFilter(watched, event);
//}
//
//
//int main(int argc, char** argv)
//{
//	QApplication app(argc, argv);
//
//	AppFilter* appFilter1 = new AppFilter("app filter1");
//	AppFilter* appFilter2 = new AppFilter("app filter2");
//	app.installEventFilter(appFilter1);
//	app.installEventFilter(appFilter2);
//
//	ReceiverFilter* receiverFilter1 = new ReceiverFilter("receiver filter1");
//	ReceiverFilter* receiverFilter2 = new ReceiverFilter("receiver filter2");
//
//	MyDrawboard2 myDrawBoard;
//	myDrawBoard.show();
//	myDrawBoard.installEventFilter(receiverFilter1);
//	myDrawBoard.installEventFilter(receiverFilter2);
//
//	return app.exec();
//}


/**========================»æ»­°å3==============================*/
//#include "mydrawboard3.h"
//
//int main(int argc,char** argv)
//{
//	QApplication app(argc, argv);
//
//	MyDrawboard3 myDrawBoard;
//	myDrawBoard.show();
//
//	return app.exec();
//}

/**========================¶ÔÏóÊ÷==============================*/
//#include "mybutton.h"
//#include <QMainWindow>
//
//int main(int argc, char** argv)
//{
//	QApplication app(argc, argv);
//
//	QMainWindow mw;
//	MyButton* pBtn1 = new MyButton(&mw);
//	MyButton* pBtn2 = new MyButton(&mw);
//	pBtn2->move(50, 50);
//
//	pBtn1->setText("btn1");
//	pBtn2->setText("btn2");
//
//	mw.show();
//
//	return app.exec();
//}

/**========================¶¨Ê±Æ÷==============================*/

#include <QObject>
#include <QTimer>
#include <QDebug>

class MyCounter :public QObject
{
	QOBJECT_H
public:
	MyCounter(QObject* parent = nullptr){}

protected:
	void timerEvent(QTimerEvent *event) override;
};

void MyCounter::timerEvent(QTimerEvent *event)
{
	qDebug() << "hello qt.";
}

int main(int argc, char** argv)
{
	QApplication app(argc, argv);

	//MyCounter counter;
	//counter.startTimer(1000);

	//QTimer* timer = new QTimer;
	//QObject::connect(timer, &QTimer::timeout, []() {
	//	qDebug() << "hello qt.";
	//});
	//timer->start(1000);

	QTimer::singleShot(1000, []() {
		qDebug() << "hello qt.";
	});

	return app.exec();
}


