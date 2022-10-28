#include <QtWidgets/QApplication>
#include <QWidget>
#include <QPushButton>
#include <QMouseEvent>
#include <QSizeGrip>
#include <QDebug>

class MyWindow :public QWidget
{
public:
	MyWindow(QWidget* parent = nullptr)
		:QWidget(parent)
	{
		setWindowFlags(Qt::FramelessWindowHint);
		resize(500, 500);
		setUi();
		m_pSizeGrip = new QSizeGrip(this);
	}
protected:
	void resizeEvent(QResizeEvent *event) override
	{
		m_pCloseBtn->move(width() - m_nBtnWidth, m_nTopMargin);
		m_pMaxBtn->move(width() - 2 * m_nBtnWidth, m_nTopMargin);
		m_pMinBtn->move(width() - 3 * m_nBtnWidth, m_nTopMargin);
	}	
	void mousePressEvent(QMouseEvent *event) override
	{
		if (event->button() == Qt::LeftButton)
		{
			m_bMoveWindow = true;
			m_tOrigin2Press =  event->globalPos() - pos();
		}
	}
	void mouseMoveEvent(QMouseEvent *event) override
	{
		if (m_bMoveWindow)
		{
			move(event->globalPos() - m_tOrigin2Press);
		}
	}
	void mouseReleaseEvent(QMouseEvent *event) override
	{
		m_bMoveWindow = false;
	}

private:
	void setUi()
	{
		addCloseMaxMinControl();
	}
	void addCloseMaxMinControl()
	{
		m_pCloseBtn = new QPushButton(QIcon(":/images/close.png"),"",this);
		m_pCloseBtn->resize(m_nBtnWidth, m_nBtnHeight);
		connect(m_pCloseBtn, &QPushButton::clicked, [=]() {this->close(); });

		m_pMaxBtn = new QPushButton(QIcon(":/images/max.png"), "", this);
		m_pMaxBtn->resize(m_nBtnWidth, m_nBtnHeight);
		connect(m_pMaxBtn, &QPushButton::clicked, [=]() {this->isFullScreen() ? this->showNormal():this->showFullScreen(); });

		m_pMinBtn = new QPushButton(QIcon(":/images/min.png"), "", this);
		m_pMinBtn->resize(m_nBtnWidth, m_nBtnHeight);
		connect(m_pMinBtn, &QPushButton::clicked, [=]() {this->showMinimized(); });
	}
	
	int m_nBtnWidth = 40;
	int m_nBtnHeight = 25;
	int m_nTopMargin = 0;

	QPushButton* m_pCloseBtn;
	QPushButton* m_pMaxBtn;
	QPushButton* m_pMinBtn;

	bool	m_bMoveWindow = false;
	QPoint  m_tOrigin2Press;      // 鼠标按下时,原点到按下点的向量

	QSizeGrip * m_pSizeGrip;	  // 可拖动句柄
};



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	MyWindow w;
	w.show();

    return a.exec();
}
