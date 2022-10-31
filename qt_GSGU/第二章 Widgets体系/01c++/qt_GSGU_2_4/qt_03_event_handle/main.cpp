#pragma execution_character_set("utf-8")
#include <QtWidgets/QApplication>
#include <QWidget>
#include <QMoveEvent>
#include <QKeyEvent>
#include <QMimeData>
#include <QUrl>
#include <QPainter>
#include <QPen>
#include <QtMath>
#include <QMenu>
#include <QAction>
#include <QDebug>

/**
	显示关闭事件
*/
class MyWidget:public QWidget
{
public:
	MyWidget(QWidget* parent=nullptr)
		:QWidget(parent)
	{
		setWindowTitle("QWidget显示关闭事件");
		resize(400, 400);
	}
protected:
	void showEvent(QShowEvent *event) override
	{
		qDebug() << "----------> show event";
	}
	void closeEvent(QCloseEvent *event) override
	{
		qDebug() << "----------> close event";
	}
};

/**
	移动事件
*/
class MyWidget2 :public QWidget
{
public:
	MyWidget2(QWidget* parent = nullptr)
		:QWidget(parent)
	{
		setWindowTitle("QWidget移动事件");
		resize(400, 400);
	}
protected:
	void moveEvent(QMoveEvent *event) override
	{
		qDebug() << "----------> move event" << event->pos();
	}
};

/**
	调整大小事件
*/
class MyWidget3 :public QWidget
{
public:
	MyWidget3(QWidget* parent = nullptr)
		:QWidget(parent)
	{
		setWindowTitle("QWidget调整大小事件");
		resize(400, 400);
	}
protected:
	void resizeEvent(QResizeEvent *event) override
	{
		qDebug() << "--------> resize event old size: " << event->oldSize() << " cur size: " << event->size();
	}
};


/**
	鼠标进入离开事件
*/
class MyWidget4 :public QWidget
{
public:
	MyWidget4(QWidget* parent = nullptr)
		:QWidget(parent)
	{
		setWindowTitle("QWidget鼠标进入离开事件");
		resize(400, 400);
	}
protected:
	void enterEvent(QEvent *event) override
	{
		setStyleSheet("background-color:yellow;");
	}
	void leaveEvent(QEvent *event) override
	{
		setStyleSheet("background-color:blue;");
	}
};

/**
	鼠标按下移动松开事件
*/
class MyWidget5 :public QWidget
{
public:
	MyWidget5(QWidget* parent = nullptr)
		:QWidget(parent)
	{
		setWindowTitle("QWidget鼠标按下移动松开事件");
		resize(400, 400);
	}
protected:
	void mousePressEvent(QMouseEvent *event) override
	{
		qDebug() << "-----> mouse press.";
	}
	void mouseMoveEvent(QMouseEvent *event) override
	{
		qDebug() << "-----> mouse move.";
	}
	void mouseReleaseEvent(QMouseEvent *event) override
	{
		qDebug() << "-----> mouse realease.";
	}

};


/**
	键盘事件
*/
class MyWidget6 :public QWidget
{
public:
	MyWidget6(QWidget* parent = nullptr)
		:QWidget(parent)
	{
		setWindowTitle("QWidget键盘事件");
		resize(400, 400);
	}
protected:
	void keyPressEvent(QKeyEvent *event) override
	{
		qDebug() << "------> key press evt." << " key is " << event->key();
	}
	void keyReleaseEvent(QKeyEvent *event) override
	{
		qDebug() << "------> key release evt." << " key is " << event->key();
	}
};

/**
	焦点事件
*/
class MyWidget7 :public QWidget
{
public:
	MyWidget7(QWidget* parent = nullptr)
		:QWidget(parent)
	{
		setWindowTitle("QWidget焦点事件");
		resize(400, 400);
	}
protected:
	void focusInEvent(QFocusEvent *event) override
	{
		qDebug() << "focus in evt." << this;
	}
	void focusOutEvent(QFocusEvent *event) override
	{
		qDebug() << "focus out evt." << this;
	}
};


/**
	拖拽事件
*/
class MyWidget8 :public QWidget
{
public:
	MyWidget8(QWidget* parent = nullptr)
		:QWidget(parent)
	{
		setWindowTitle("QWidget拖拽事件");
		resize(400, 400);

		setAcceptDrops(true);
	}
protected:
	void dragEnterEvent(QDragEnterEvent *event) override
	{
		qDebug() << "drag enter event. pos is " << event->pos();
		event->setAccepted(true);
	}
	void dragMoveEvent(QDragMoveEvent *event) override
	{
		qDebug() << "drag move event. pos is " << event->pos();
	}
	void dragLeaveEvent(QDragLeaveEvent *event) override
	{
		qDebug() << "drag leave event.";
	}
	void dropEvent(QDropEvent *event) override
	{
		qDebug() << "drop event.";
		const QMimeData* mimeData = event->mimeData();
		if (mimeData->hasUrls())
		{
			QList<QUrl> urlList = mimeData->urls();
			qDebug() << urlList;
			setWindowTitle(urlList[0].path());
		}
	}
};


/**
	绘制事件
*/
class MyWidget9 :public QWidget
{
public:
	MyWidget9(QWidget* parent = nullptr)
		:QWidget(parent)
	{
		setWindowTitle("QWidget绘制事件");
		resize(400, 400);
	}
protected:
	void paintEvent(QPaintEvent *event) override
	{
		QPainter painter(this);
		painter.setViewport(50, 50, width() - 100, height() - 100);
		painter.setWindow(-10, 2, 20, -4);
		painter.fillRect(-10, 2, 20, -4, Qt::black);

		QPen pen;
		pen.setColor(Qt::white);
		pen.setWidthF(3.0);
		pen.setCosmetic(true);
		painter.setPen(pen);
		painter.drawLine(QPointF(-10, 0), QPointF(10, 0));   // x axis
		painter.drawLine(QPointF(0, 2), QPointF(0, -2));     // y axis

		pen.setColor(Qt::green);
		pen.setWidth(0);
		painter.setPen(pen);

		for (double x = -10; x < 10; x += 0.01)
		{
			double y = qSin(x);
			painter.drawPoint(QPointF(x, y));
		}
	}
};


/**
	改变事件
*/
class MyWidget10 :public QWidget
{
public:
	MyWidget10(QWidget* parent = nullptr)
		:QWidget(parent)
	{
		setWindowTitle("QWidget改变事件");
		resize(400, 400);
	}
protected:
	void changeEvent(QEvent *) override
	{
		qDebug() << "change event.";
	}
};


/**
	右键菜单栏事件
*/
class MyWidget11 :public QWidget
{
public:
	MyWidget11(QWidget* parent = nullptr)
		:QWidget(parent)
	{
		setWindowTitle("QWidget右键菜单栏事件");
		resize(400, 400);
		m_pContextMenu = new QMenu(this);
		m_pBackAct = new QAction(QIcon(":/images/back.png"),"返回", this);
		connect(m_pBackAct, &QAction::triggered, []() {qDebug() << "返回了........."; });
	}
protected:
	void contextMenuEvent(QContextMenuEvent *event) override
	{
		qDebug() << "right mouse press.";
		m_pContextMenu->clear();
		m_pContextMenu->addAction(m_pBackAct);
		m_pContextMenu->addAction("前进");
		m_pContextMenu->addAction("重新加载");
		m_pContextMenu->addSeparator();
		m_pContextMenu->addAction("另存为");
		m_pContextMenu->addSeparator();
		m_pContextMenu->addAction("检查");
		m_pContextMenu->move(event->globalPos());
		m_pContextMenu->show();
	}
private: 
	QMenu*		m_pContextMenu;
	QAction*	m_pBackAct;
};

/**
	事件的传递
*/
class BigWidget :public QWidget
{
public:
	BigWidget(QWidget* parent = nullptr)
		:QWidget(parent)
	{
		resize(300, 300);
		setStyleSheet("background-color:red;");
	}
protected:
	void mousePressEvent(QMouseEvent *event) override
	{
		qDebug() << "Big Widget";
	}
};

class SmallWidget :public QWidget
{
public:
	SmallWidget(QWidget* parent = nullptr)
		:QWidget(parent)
	{
		resize(100, 100);
		setStyleSheet("background-color:green;");
	}
protected:
	void mousePressEvent(QMouseEvent *event) override
	{
		qDebug() << "Small Widget";
		event->ignore();
	}
};
class MyWidget12 :public QWidget
{
public:
	MyWidget12(QWidget* parent = nullptr)
		:QWidget(parent)
	{
		resize(400, 400);
		BigWidget* bw = new BigWidget(this);
		SmallWidget* sw = new SmallWidget(bw);
	}
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	MyWidget11 w;
	w.show();

    return a.exec();
}
