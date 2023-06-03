#pragma once

#include <QLayout>
#include <QRect>
#include <QStyle>

/** @brief Qt流式布局实现 */
class FlowLayout : public QLayout
{
public:
	explicit FlowLayout(QWidget *parent, int margin = -1, int hSpacing = -1, int vSpacing = -1);
	explicit FlowLayout(int margin = -1, int hSpacing = -1, int vSpacing = -1);
	~FlowLayout();

	/** 获取当前水平及竖直间距 */
	int horizontalSpacing() const;
	int verticalSpacing() const;

	/** 常规基类布局函数重写 */
	void addItem(QLayoutItem *item) override;
	Qt::Orientations expandingDirections() const override;
	bool hasHeightForWidth() const override;
	int heightForWidth(int) const override;
	int count() const override;
	QLayoutItem *itemAt(int index) const override;
	QSize minimumSize() const override;
	void setGeometry(const QRect &rect) override;
	QSize sizeHint() const override;
	QLayoutItem *takeAt(int index) override;

private:

	/** 设置布局 */
	int doLayout(const QRect &rect, bool testOnly) const;

	/** 像素间距设置 */
	int smartSpacing(QStyle::PixelMetric pm) const;

	QList<QLayoutItem *>	m_listItems;		///< 容器列表
	int						m_nHSpace;			///< 竖直间距
	int						m_nVSpace;			///< 水平间距
};