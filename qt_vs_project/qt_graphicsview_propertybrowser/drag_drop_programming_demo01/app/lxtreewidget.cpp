#pragma execution_character_set("utf-8")
#include "lxtreewidget.h"
#include "common.h"

#include <QDebug>
#include <QMouseEvent>
#include <QtWidgets/QApplication>

LxTreeWidget::LxTreeWidget(QWidget *parent)
	: QTreeWidget(parent)
{
	addItem();

}

LxTreeWidget::~LxTreeWidget()
{
}

void LxTreeWidget::mouseMoveEvent(QMouseEvent *event)
{
	// 不允许父级 tree widget item drag and drop 
	if (currentItem()->child(0))
		return;


	QTreeWidget::mouseMoveEvent(event);
}

void LxTreeWidget::addItem()
{
	QIcon icon;
	icon.addFile(QString::fromUtf8(":/icons/move.png"), QSize(), QIcon::Normal, QIcon::Off);
	QTreeWidgetItem *item = new QTreeWidgetItem(this);
	item->setText(0, " DI/DO");
	QTreeWidgetItem *item1 = new QTreeWidgetItem(item);
	item1->setIcon(0, icon);
	item1->setText(0, "检查DI");
	item1->setData(0, vizItemTypeRole, LxVizItemType::CheckDI);
	QTreeWidgetItem *item2 = new QTreeWidgetItem(item);
	item2->setIcon(0, icon);
	item2->setText(0, "等待DI");
	item2->setData(0, vizItemTypeRole, LxVizItemType::WaitDI);
	QTreeWidgetItem *item3 = new QTreeWidgetItem(item);
	item3->setIcon(0, icon);
	item3->setText(0, "设置DO");
	item3->setData(0, vizItemTypeRole, LxVizItemType::SetDO);
	QTreeWidgetItem *item4 = new QTreeWidgetItem(this);
	item4->setText(0, " 基本运动");
	QTreeWidgetItem *item5 = new QTreeWidgetItem(item4);
	item5->setIcon(0, icon);
	item5->setText(0, "按阵列运动");
	QTreeWidgetItem *item6 = new QTreeWidgetItem(item4);
	item6->setIcon(0, icon);
	item6->setText(0, "相对移动");
	item6->setData(0, vizItemTypeRole, LxVizItemType::RelMove);
	QTreeWidgetItem *item7 = new QTreeWidgetItem(item4);
	item7->setIcon(0, icon);
	item7->setText(0, "移动");
	item7->setData(0, vizItemTypeRole, LxVizItemType::Move);
	QTreeWidgetItem *item8 = new QTreeWidgetItem(this);
	item8->setText(0, " 工具");
	QTreeWidgetItem *item9 = new QTreeWidgetItem(item8);
	item9->setIcon(0, icon);
	item9->setText(0, "开始");
	item9->setData(0, vizItemTypeRole, LxVizItemType::Start);
	QTreeWidgetItem *item10 = new QTreeWidgetItem(item8);
	item10->setIcon(0, icon);
	item10->setText(0, "新建子项目");
	QTreeWidgetItem *item11 = new QTreeWidgetItem(item8);
	item11->setIcon(0, icon);
	item11->setText(0, "新建子项目");
	QTreeWidgetItem *item12 = new QTreeWidgetItem(item8);
	item12->setIcon(0, icon);
	item12->setText(0, "新建子项目");
	QTreeWidgetItem *item13 = new QTreeWidgetItem(this);
	item13->setText(0, " 拓扑");
	QTreeWidgetItem *item14 = new QTreeWidgetItem(item13);
	item14->setIcon(0, icon);
	item14->setText(0, "新建子项目");
	QTreeWidgetItem *item15 = new QTreeWidgetItem(this);
	item15->setText(0, " 服务");
	QTreeWidgetItem *item16 = new QTreeWidgetItem(item15);
	item16->setIcon(0, icon);
	item16->setText(0, "新建子项目");
	QTreeWidgetItem *item17 = new QTreeWidgetItem(this);
	item17->setText(0, " 机器人相关工具");
	QTreeWidgetItem *item18 = new QTreeWidgetItem(item17);
	item18->setIcon(0, icon);
	item18->setText(0, "新建子项目");
	QTreeWidgetItem *item19 = new QTreeWidgetItem(item17);
	item19->setIcon(0, icon);
	item19->setText(0, "新建子项目");
	QTreeWidgetItem *item20 = new QTreeWidgetItem(item17);
	item20->setIcon(0, icon);
	item20->setText(0, "新建子项目");
	QTreeWidgetItem *item21 = new QTreeWidgetItem(this);
	item21->setText(0, " 码垛");
	QTreeWidgetItem *item22 = new QTreeWidgetItem(item21);
	item22->setIcon(0, icon);
	item22->setText(0, "新建子项目");
	QTreeWidgetItem *item23 = new QTreeWidgetItem(item21);
	item23->setIcon(0, icon);
	item23->setText(0, "新建子项目");
	QTreeWidgetItem *item24 = new QTreeWidgetItem(item21);
	item24->setIcon(0, icon);
	item24->setText(0, "新建子项目");
	QTreeWidgetItem *item25 = new QTreeWidgetItem(this);
	item25->setText(0, " 自定义");
	QTreeWidgetItem *item26 = new QTreeWidgetItem(item25);
	item26->setIcon(0, icon);
	item26->setText(0, "新建子项目");
	QTreeWidgetItem *item27 = new QTreeWidgetItem(this);
	item27->setText(0, " 视觉");
	QTreeWidgetItem *item28 = new QTreeWidgetItem(item27);
	item28->setIcon(0, icon);
	item28->setText(0, "新建子项目");
	QTreeWidgetItem *item29 = new QTreeWidgetItem(item27);
	item29->setIcon(0, icon);
	item29->setText(0, "新建子项目");
	QTreeWidgetItem *item30 = new QTreeWidgetItem(item27);
	item30->setIcon(0, icon);
	item30->setText(0, "新建子项目");

	setDragEnabled(true);
	setIndentation(10);
	setHeaderHidden(true);

}

