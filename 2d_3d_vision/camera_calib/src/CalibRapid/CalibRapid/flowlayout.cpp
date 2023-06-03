#include <QtWidgets>
#include "flowlayout.h"

/** *******************************************************************
* @brief  	   窗体构造
* @param[in]   parent —— 父窗体
* @param[in]   margin —— 边间距
* @param[in]   hSpacing —— 水平间距
* @param[in]   vSpacing —— 垂直间距
* @return	   void
******************************************************************** */
FlowLayout::FlowLayout(QWidget *parent, int margin, int hSpacing, int vSpacing)
	: QLayout(parent), m_nHSpace(hSpacing), m_nVSpace(vSpacing)
{
	setContentsMargins(margin, margin, margin, margin);
}

/** *******************************************************************
* @brief  	   窗体构造
* @param[in]   parent —— 父窗体
* @param[in]   margin —— 边间距
* @param[in]   hSpacing —— 水平间距
* @param[in]   vSpacing —— 垂直间距
* @return	   void
******************************************************************** */
FlowLayout::FlowLayout(int margin, int hSpacing, int vSpacing)
	: m_nHSpace(hSpacing), m_nVSpace(vSpacing)
{
	setContentsMargins(margin, margin, margin, margin);
}

/** *******************************************************************
* @brief  	   窗体析构
* @return	   void
******************************************************************** */
FlowLayout::~FlowLayout()
{
	QLayoutItem *item;
	while ((item = takeAt(0)))
		delete item;
}

/** *******************************************************************
* @brief  	   添加列表物体
* @param[in]   item —— 物体
* @return	   void
******************************************************************** */
void FlowLayout::addItem(QLayoutItem *item)
{
	m_listItems.append(item);
}

/** *******************************************************************
* @brief  	   获取水平间距
* @return	   int
******************************************************************** */
int FlowLayout::horizontalSpacing() const
{
	if (m_nHSpace >= 0) 
	{
		return m_nHSpace;
	}
	else 
	{
		return smartSpacing(QStyle::PM_LayoutHorizontalSpacing);
	}
}

/** *******************************************************************
* @brief  	   获取竖直间距
* @return	   int
******************************************************************** */
int FlowLayout::verticalSpacing() const
{
	if (m_nVSpace >= 0) 
	{
		return m_nVSpace;
	}
	else 
	{
		return smartSpacing(QStyle::PM_LayoutVerticalSpacing);
	}
}

/** *******************************************************************
* @brief  	   获取列表个数
* @return	   int
******************************************************************** */
int FlowLayout::count() const
{
	return m_listItems.size();
}

/** *******************************************************************
* @brief  	   获取某个列表物体
* @param[in]   index —— 序号
* @return	   列表物体
******************************************************************** */
QLayoutItem *FlowLayout::itemAt(int index) const
{
	return m_listItems.value(index);
}

/** *******************************************************************
* @brief  	   获取某个列表物体
* @param[in]   index —— 序号
* @return	   列表物体
******************************************************************** */
QLayoutItem *FlowLayout::takeAt(int index)
{
	if (index >= 0 && index < m_listItems.size())
		return m_listItems.takeAt(index);
	else
		return 0;
}

/** *******************************************************************
* @brief  	   拓展方向
* @return	   列表物体
******************************************************************** */
Qt::Orientations FlowLayout::expandingDirections() const
{
	return 0;
}

/** *******************************************************************
* @brief  	   获取窗体宽度下的高度
* @return	   
******************************************************************** */
bool FlowLayout::hasHeightForWidth() const
{
	return true;
}

/** *******************************************************************
* @brief  	   获取窗体宽度下的高度
* @param[in]   width —— 宽度
* @return
******************************************************************** */
int FlowLayout::heightForWidth(int width) const
{
	int height = doLayout(QRect(0, 0, width, 0), true);
	return height;
}

/** *******************************************************************
* @brief  	   设置窗体几何矩形
* @param[in]   rect —— 几何矩形
* @return
******************************************************************** */
void FlowLayout::setGeometry(const QRect &rect)
{
	QLayout::setGeometry(rect);
	doLayout(rect, false);
}

/** *******************************************************************
* @brief  	   最小化
* @return
******************************************************************** */
QSize FlowLayout::sizeHint() const
{
	return minimumSize();
}

/** *******************************************************************
* @brief  	   最小化
* @return
******************************************************************** */
QSize FlowLayout::minimumSize() const
{
	QSize size;
	QLayoutItem *item;
	foreach(item, m_listItems)
		size = size.expandedTo(item->minimumSize());

	size += QSize(2 * margin(), 2 * margin());
	return size;
}

/** *******************************************************************
* @brief  	   设置布局
* @param[in]   rect —— 几何矩形
* @param[in]   testOnly —— 是否仅测试
* @return
******************************************************************** */
int FlowLayout::doLayout(const QRect &rect, bool testOnly) const
{
	int left, top, right, bottom;
	getContentsMargins(&left, &top, &right, &bottom);
	QRect effectiveRect = rect.adjusted(+left, +top, -right, -bottom);
	int x = effectiveRect.x();
	int y = effectiveRect.y();
	int lineHeight = 0;

	QLayoutItem *item;
	foreach(item, m_listItems) 
	{
		QWidget *wid = item->widget();
		int spaceX = horizontalSpacing();
		if (spaceX == -1)
			spaceX = wid->style()->layoutSpacing(
				QSizePolicy::PushButton, QSizePolicy::PushButton, Qt::Horizontal);
		int spaceY = verticalSpacing();
		if (spaceY == -1)
			spaceY = wid->style()->layoutSpacing(
				QSizePolicy::PushButton, QSizePolicy::PushButton, Qt::Vertical);
		int nextX = x + item->sizeHint().width() + spaceX;
		if (nextX - spaceX > effectiveRect.right() && lineHeight > 0) 
		{
			x = effectiveRect.x();
			y = y + lineHeight + spaceY;
			nextX = x + item->sizeHint().width() + spaceX;
			lineHeight = 0;
		}

		if (!testOnly)
			item->setGeometry(QRect(QPoint(x, y), item->sizeHint()));

		x = nextX;
		lineHeight = qMax(lineHeight, item->sizeHint().height());
	}
	return y + lineHeight - rect.y() + bottom;
}

/** *******************************************************************
* @brief  	   小间距设置
* @param[in]   pm —— 像素
* @return
******************************************************************** */
int FlowLayout::smartSpacing(QStyle::PixelMetric pm) const
{
	QObject *parent = this->parent();
	if (!parent) {
		return -1;
	}
	else if (parent->isWidgetType()) {
		QWidget *pw = static_cast<QWidget *>(parent);
		return pw->style()->pixelMetric(pm, 0, pw);
	}
	else {
		return static_cast<QLayout *>(parent)->spacing();
	}
}

