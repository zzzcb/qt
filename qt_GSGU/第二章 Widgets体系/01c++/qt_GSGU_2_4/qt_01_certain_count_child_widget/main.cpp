#pragma execution_character_set("utf-8")
#include <QtWidgets/QApplication>
#include <QWidget>

class Demo :public QWidget
{
public:
	Demo(int totalCnt, int colCnt,QWidget* parent=nullptr)
		:QWidget(parent), m_nTotalCnt(totalCnt),m_nColCnt(colCnt)
	{
		if (totalCnt <= 0 || colCnt <= 0)
			totalCnt = colCnt = 1;

		setWindowTitle("我不是Qt");
		move(300, 300);
		resize(500, 500);

		setupUi();
	}

private:
	void setupUi()
	{
		int rowCnt = m_nTotalCnt / m_nColCnt;
		int itemW = width() / m_nColCnt;
		int itemH = height() / rowCnt;
		for (int r = 0; r < rowCnt; r++)
		{
			for (int c = 0; c < m_nColCnt; c++)
			{
				if((r+1)*m_nColCnt + (c+1) > m_nTotalCnt)
					break;
				QWidget* childItem = new QWidget(this);
				childItem->move(c*itemW, r*itemH);
				childItem->resize(itemW, itemH);
				childItem->setStyleSheet("background-color:red;border:1px solid yellow;");
			}
		}
	}

	int m_nTotalCnt;	///< 总数    
	int m_nColCnt;		///< 列数
};

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	Demo demo(50, 3);
	demo.show();

	return a.exec();
}
