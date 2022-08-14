#include "lxqbuttongroup.h"

#include <QMouseEvent>
#include <QScrollArea>
#include <QApplication>


lxQButtonGroup::lxQButtonGroup(QWidget *parent):
	QWidget(parent)
{
	setMouseTracking(true); // 鼠标悬浮 mouseMoveEvent 事件
}

lxQButtonGroup::~lxQButtonGroup()
{

}

void lxQButtonGroup::setButtonsDir(bool bHor)
{
	mb_hor = bHor;
}

void lxQButtonGroup::setButtonSize(int l, int w)
{
	mn_l = l;
	mn_w = w;
}

void lxQButtonGroup::addButton(QString iconPath,QString toolTip, bool bCheckable, bool bDragable)
{
	static int btnNum = 0;
	MyButton* btn= new MyButton(mn_l, mn_w,iconPath,QString("btn-%1").arg(btnNum),this);
	btnNum++;

	btn->setCheckable(bCheckable);
	btn->setDragable(bDragable);
	btn->setToolTip(toolTip);

	mvp_button.push_back(btn);
	updateButtons();
}


bool lxQButtonGroup::buttonChecked(QString btnId)
{
	for (auto btn : mvp_button)
	{
		if (btn->id() == btnId)
			return btn->checked();
	}
	return false;
}

void lxQButtonGroup::mousePressEvent(QMouseEvent *event)
{
	QPoint curPos= event->pos();

	QWidget* child= childAt(curPos);

	// 当前无btn
	if(!child)
		return;
	else 
	{
		// 如果此时已经上了背景色,就反转下
		if (child == mp_activeBtn)
		{
			((MyButton*)child)->setBackgroundColor(false);
			mp_activeBtn = nullptr;
			return;
		}

		mp_activeBtn = (MyButton*)child;

		// 当前鼠标所在的item 上背景色,其他不上
		for (auto& btn : mvp_button)
		{
			if (btn == child)
				btn->setBackgroundColor(true);
			else
				btn->setBackgroundColor(false);
		}

	}
}


void lxQButtonGroup::mouseMoveEvent(QMouseEvent *event)
{

}

void lxQButtonGroup::updateButtons()
{
	int xOff, yOff = 0;
	if (mb_hor)
	{
		xOff = mn_l;
		yOff = 0;
	}
	else
	{
		xOff = 0;
		yOff = mn_w;
	}

	for (int i=0;i<mvp_button.size();i++)
	{
		mvp_button[i]->move(i*xOff,i*yOff);
	}

}

//  ============================My Button=============================
MyButton::MyButton(int l,int w, QString iconPath, QString btnId, QWidget*parent)
	:QWidget(parent),mn_l(l),mn_w(w), mn_penWidth(1), mstr_iconPath(iconPath),mstr_btnId(btnId)
{
	setStyleSheet("QWidget{background-color:rgb(29,29,29);}");
	setFixedSize(l, w);
	setMouseTracking(true); // 鼠标悬浮 mouseMoveEvent 事件


	QPainter p(this);
	QPen pen;
	pen.setWidth(mn_penWidth);
	pen.setColor(Qt::lightGray);

	p.setPen(pen);
	//p.drawRect(0, 0, mn_l - 2 * mn_penWidth, mn_w - 2 * mn_penWidth);
	p.drawRect(0, 0, mn_l - mn_penWidth, mn_w - mn_penWidth);
}

MyButton::~MyButton()
{

}

QString MyButton::id()
{
	return mstr_btnId;
}

bool MyButton::checked()
{
	return mb_check;
}

void MyButton::setPenWidth(int width)
{
	mn_penWidth = width;
}

void MyButton::setBackgroundColor(bool enable)
{
	if (enable && mb_checkable)
	{
		mb_check = true;
		setStyleSheet(
			"QWidget{background-color:rgb(71,114,179);}");   // press
	}

	else
	{
		mb_check = false;
		setStyleSheet(
			"QWidget{background-color:rgb(29,29,29);}"      // origin
			"QWidget:hover{background-color:rgb(48,48,48);}");// hover 
	}

}

void MyButton::setCheckable(bool enable)
{
	mb_checkable = enable;
}

void MyButton::setDragable(bool enable)
{
	mb_dragable = enable;
}

void MyButton::paintEvent(QPaintEvent *event)
{
	QPainter p(this);
	QPen pen;
	pen.setWidth(mn_penWidth);
	pen.setColor(QColor(70,70,70));

	p.setPen(pen);
	//p.drawRect(0, 0, mn_l - 2 * mn_penWidth, mn_w - 2 * mn_penWidth);
	p.drawRect(0, 0, mn_l - mn_penWidth, mn_w - mn_penWidth);
	
	qreal extra = 5;
	QRect r(extra, extra, mn_l - mn_penWidth - 2 * extra, mn_w - mn_penWidth - 2 * extra);

	// 绘制图标
	p.drawPixmap(r,QPixmap(mstr_iconPath));
}

void MyButton::mousePressEvent(QMouseEvent *event)
{
	m_pressPoint = event->screenPos();
	mb_moving = false;

	//setStyleSheet("background-color:red;");

	event->ignore();  // 事件将会传递给父亲
}

#include <QDrag>
#include <QMimeData>

void MyButton::mouseMoveEvent(QMouseEvent *event)
{
	if ( !mb_dragable || QLineF(event->screenPos(), m_pressPoint).length() < QApplication::startDragDistance() || mb_moving)
		return;

	mb_moving = true;

	QDrag * drag = new QDrag(this);
	QMimeData* mimeData = new QMimeData();
	mimeData->setText(mstr_btnId);

	QPixmap pixmap(":/images/box.png");

	drag->setPixmap(pixmap.scaled(50, 50));
	drag->setMimeData(mimeData);
	drag->setHotSpot(QPoint(25,25));
	drag->exec();



	event->ignore();  // 事件将会传递给父亲
}
