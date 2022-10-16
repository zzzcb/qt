#include "demo.h"

#include <QRubberBand>
#include <QLabel>
#include <QMouseEvent>
#include <QApplication>
#include <QClipboard>
#include <QDebug>

/**================= MyMimeData =================*/

MyMimeData::MyMimeData(QList<QLabel*> items)
{
	for (const auto&item : items)
	{
		if (MyLabel* lb = qobject_cast<MyLabel*>(item))
		{
			m_vpItem.push_back(lb->duplicate());
		}
	}
}

MyMimeData::~MyMimeData()
{
	for (auto& item : m_vpItem)
		delete item;

	m_vpItem.clear();
}

QList<QLabel*> MyMimeData::getItems() const
{
	return m_vpItem;
}

/**================= MyLabel =================*/

MyLabel::MyLabel(QString iconPath, QPoint pos, QWidget *parent)
	:m_pParent(parent), m_pPos(pos)
{
	setParent(parent);
	setPixmap(QPixmap(iconPath));
	move(pos);
}

QLabel * MyLabel::duplicate()
{
	MyLabel* copyLb = new MyLabel("",m_pPos);
	copyLb->setPixmap(*pixmap());
	copyLb->move(m_pPos);
	return copyLb;
}

QPoint MyLabel::getPos()
{
	return m_pPos;
}

void MyLabel::updatePos(QPoint newPos)
{
	m_pPos = newPos;
}

/**================= Demo =================*/
Demo::Demo(QWidget *parent)
    : QWidget(parent)
{
	m_pRubberBand = new QRubberBand(QRubberBand::Rectangle, this);

	MyLabel* lb1 = new MyLabel(":/images/1.png", QPoint(50, 0), this);
	MyLabel* lb2 = new MyLabel(":/images/3.png", QPoint(300, 200), this);
	MyLabel* lb3 = new MyLabel(":/images/2.png", QPoint(350, 0), this);
	MyLabel* lb4 = new MyLabel(":/images/4.png", QPoint(600, 200), this);
	MyLabel* lb5 = new MyLabel(":/images/1.png", QPoint(650, 0), this);
	MyLabel* lb6 = new MyLabel(":/images/5.png", QPoint(900, 200), this);
}

Demo::~Demo()
{
}

void Demo::mousePressEvent(QMouseEvent *event)
{
	m_tPressPos = event->pos();
	m_pRubberBand->setGeometry(QRect(m_tPressPos, QSize()));
	m_pRubberBand->show();
}

void Demo::mouseMoveEvent(QMouseEvent *event)
{
	m_pRubberBand->setGeometry(QRect(m_tPressPos, event->pos()).normalized()); ///< normalized 保证了 可以反向选择
}

void Demo::mouseReleaseEvent(QMouseEvent *event)
{
	m_vSelectedLabel.clear();

	QRect selectRect = m_pRubberBand->geometry();
	for (auto child : children())
	{
		if (child->inherits("QLabel"))
		{
			if (MyLabel* childLb = qobject_cast<MyLabel*>(child))
			{
				if (selectRect.contains(childLb->geometry()))
				{
					childLb->setStyleSheet("border:1px solid rgb(255,0,0);");
					childLb->updatePos(childLb->mapToParent(QPoint(0,0)));
					m_vSelectedLabel.push_back(childLb);
				}
				else
				{
					childLb->setStyleSheet("border:no-border;");
				}
			}
		}
	}

	m_pRubberBand->hide();
}

void Demo::keyPressEvent(QKeyEvent *event)
{
	/** 是否按下了ctrl*/
	if (event->key() == Qt::Key_Control)
	{
		m_bCtrl = true;
	}

	/** 快捷键操作*/
	switch (event->key())
	{
	case Qt::Key_C:
		if (m_bCtrl)
		{
			/** ctrl + c 拷贝选中的Item 到剪切板*/
			copyItem();
		}
		break;
	case Qt::Key_V:
		if (m_bCtrl)
		{
			/** ctrl + v 从剪切板中粘贴*/
			pasteItem();
		}
		break;
	case Qt::Key_Delete:
		deleteItem();
	}

	QWidget::keyPressEvent(event);
}

void Demo::keyReleaseEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Control)
	{
		m_bCtrl = false;
	}

	QWidget::keyReleaseEvent(event);
}

void Demo::copyItem()
{
	QList<QLabel*> copyedItem;
	for (auto item : m_vSelectedLabel)
	{
		copyedItem.push_back(item);
	}

	QApplication::clipboard()->clear();
	QApplication::clipboard()->setMimeData(new MyMimeData(copyedItem));
}

void Demo::pasteItem()
{
	/** const_cast转换符是用来移除变量的const限定符*/
	QMimeData* md = const_cast<QMimeData*>(QApplication::clipboard()->mimeData());
	MyMimeData* data = dynamic_cast<MyMimeData*>(md);
	if (data)
	{
		/** ctrl + v 将剪切板的item再复制一份加入到界面上*/
		for (const auto&item : data->getItems())
		{
			auto _item = qobject_cast<MyLabel*>(item);
			if (_item)
			{
				auto copy = _item->duplicate();
				copy->setParent(this);
				copy->move(_item->getPos() + QPoint(50, 300));
				copy->show();
			}
		}
	}
}

void Demo::deleteItem()
{
	for (auto lb:m_vSelectedLabel)
	{
		delete lb;
	}
}
