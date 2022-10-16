#pragma once

#include <QtWidgets/QWidget>
#include <QMimeData>
#include <QLabel>

class QRubberBand;


/**
	mime data,用于数据的传输,例如剪切,拷贝,复制等操作
*/
class MyMimeData :public QMimeData
{
	Q_OBJECT
public:
	MyMimeData(QList<QLabel*> items);
	~MyMimeData();
	QList<QLabel*> getItems() const;

private:
	QList<QLabel*> m_vpItem;
};

/**
	MyLabel 用于展示图片
*/
class MyLabel :public QLabel
{
	Q_OBJECT

public:
	MyLabel(QString iconPath, QPoint pos = QPoint(0, 0), QWidget *parent = nullptr);

	QLabel * duplicate();
	QPoint   getPos();

	void	 updatePos(QPoint newPos);

private:
	QWidget* m_pParent;
	QPoint   m_pPos;
};


class Demo : public QWidget
{
    Q_OBJECT

public:
    Demo(QWidget *parent = nullptr);
    ~Demo();

protected:
	void mousePressEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void mouseReleaseEvent(QMouseEvent *event) override;

	void keyPressEvent(QKeyEvent *event) override;
	void keyReleaseEvent(QKeyEvent *event) override;

private:
	void copyItem();
	void pasteItem();
	void deleteItem();

	QRubberBand *	m_pRubberBand;      ///< 橡皮筋
	QPoint			m_tPressPos;		///< 鼠标初始按下的位置
	QList<QLabel*>  m_vSelectedLabel;	///< 选中的对象

	bool m_bCtrl = false;				///< Ctrl 是否按下
};
