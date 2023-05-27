#pragma execution_character_set("utf-8")
#include <QtWidgets/QApplication>

#include <QFrame>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QScrollBar>
#include <QScrollArea>
#include <QStyle>
#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTextBrowser>

#include <QStandardItemModel>
#include <QColumnView>
#include <QHeaderView>
#include <QListView>
#include <QUndoView>
#include <QUndoStack>

#include <QTableView>
#include <QTreeView>

#include <QGraphicsView>
#include <QtCharts/QChartView>

#include <QTextBrowser>

#include <QDebug>


class MyScrollArea :public QAbstractScrollArea
{
	Q_OBJECT
public:
	MyScrollArea(QWidget* parent)
		:QAbstractScrollArea(parent)
	{
		m_pVBar = verticalScrollBar();
		m_pHBar = horizontalScrollBar();
		m_pVBar->setSingleStep(20);
		m_pHBar->setSingleStep(20);
	}
	
	void setWidget(QWidget* widget)
	{
		if (m_pWidget == widget || !widget)
			return;

		if (m_pWidget)
		{
			delete m_pWidget;
			m_pWidget = nullptr;
		}

		/** 默认左上角 */
		m_pVBar->setValue(0);
		m_pHBar->setValue(0);


		if (widget->parentWidget() != viewport())
			widget->setParent(viewport());
		if (!widget->testAttribute(Qt::WA_Resized))
			widget->resize(widget->sizeHint());

		m_pWidget = widget;
		m_pWidget->installEventFilter(this);

		updateScrollBars();
		m_pWidget->show();
	}
protected:
	void scrollContentsBy(int dx, int dy) override
	{
		if (!m_pWidget)
			return;
		updateWidgetPosition();
	}

private:
	void updateWidgetPosition()
	{
		Qt::LayoutDirection dir = layoutDirection();
		QRect scrolled = QStyle::visualRect(dir, viewport()->rect(), QRect(QPoint(-m_pHBar->value(), -m_pVBar->value()), m_pWidget->size()));
		QRect aligned = QStyle::alignedRect(dir, Qt::AlignLeft, m_pWidget->size(), viewport()->rect());
		m_pWidget->move(m_pWidget->width() < viewport()->width() ? aligned.x() : scrolled.x(),
			m_pWidget->height() < viewport()->height() ? aligned.y() : scrolled.y());
	}
	void updateScrollBars()
	{
		if (!m_pWidget)
			return;
		QSize p = viewport()->size();
		QSize v = m_pWidget->size();

		m_pHBar->setRange(0, v.width() - p.width());
		m_pHBar->setPageStep(p.width());
		m_pVBar->setRange(0, v.height() - p.height());
		m_pVBar->setPageStep(p.height());
		updateWidgetPosition();
	}

	QScrollBar* m_pVBar;
	QScrollBar* m_pHBar;

	QWidget* m_pWidget = nullptr;
};

class StrResultDisplay :public QDialog
{
	Q_OBJECT
public:
	StrResultDisplay(QWidget* parent = nullptr);
	void showResult(QString result);
private:
	QHBoxLayout* m_pHLayout;
};
StrResultDisplay::StrResultDisplay(QWidget* parent /*= nullptr*/)
	:QDialog(parent)
{
	// h layout
	QHBoxLayout* pMainLayout = new QHBoxLayout(this);
	pMainLayout->setContentsMargins(0, 0, 0, 0);

	QScrollArea *scrollArea = new QScrollArea;
	scrollArea->setWidgetResizable(true); // very important
	pMainLayout->addWidget(scrollArea);

	// real container
	QWidget* realContainer = new QWidget;
	scrollArea->setWidget(realContainer);

	m_pHLayout = new QHBoxLayout(realContainer);
	realContainer->setLayout(m_pHLayout);

	resize(155, 155);
}

void StrResultDisplay::showResult(QString result)
{
	QVBoxLayout * vLayout = new QVBoxLayout;
	vLayout->setAlignment(Qt::AlignVCenter);

	QTextBrowser * browser = new QTextBrowser;
	browser->setText(result);
	vLayout->addWidget(browser);

	m_pHLayout->addLayout(vLayout);
	show();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	QWidget* mw = new QWidget;

	/** 1 QFrame style(shape,shadow) */
	//QFrame* frame = new QFrame(mw);
	////frame->setFrameRect(QRect(20,20,50,50));
	////frame->setStyleSheet("background:red;");
	//frame->setFrameStyle(QFrame::Box | QFrame::Raised);
	//frame->move(100, 100);

	///** QFrame line width */
	//frame->resize(100, 100);
	//frame->setLineWidth(10);	// default value is 1 px
	//frame->setMidLineWidth(5);	// default value is 0 px 
	//qDebug() << "--------------> "<< frame->frameWidth();// depends on style(25)

	///** QFrame style can't use with QSS */
	//frame->setStyleSheet("border:3px solid red;");
	//qDebug() << "--------------> " << frame->frameWidth();// depends on style(25)

	//QPlainTextEdit * pteWidget = new QPlainTextEdit(mw);
	//pteWidget->setFrameStyle(QFrame::Box | QFrame::Raised);
	//pteWidget->setLineWidth(10);
	////pteWidget->setStyleSheet("border:3px solid red;");
	//pteWidget->move(100, 100);

	/** 2 QAbstractScrollArea */
	//QScrollArea* area = new QScrollArea(mw);
	//QPushButton* btn = new QPushButton("btn");
	//area->resize(100, 100);
	//area->setWidget(btn);
	//qDebug() << "view port " << area->viewport();
	//qDebug() << "btn parent" << btn->parent();
	////view port  QWidget(0x163d10939b0, name = "qt_scrollarea_viewport")
	////btn parent QWidget(0x163d10939b0, name = "qt_scrollarea_viewport")

	//MyScrollArea* mySA = new MyScrollArea(mw);
	//QPushButton* btn = new QPushButton("Big Btn Big Btn Big Btn");
	//mySA->resize(100, 100);
	//mySA->setWidget(btn);

	//StrResultDisplay disp;
	//disp.showResult("zzzzzzzzzzzzzzzzzzzzzzzzzzz");

	///** 3 QColumnView */
	//// 创建数据模型
	//QStandardItemModel model;
	//QStandardItem *rootItem = model.invisibleRootItem();

	//QStandardItem *item1 = new QStandardItem("Item 1");
	//rootItem->appendRow(item1);
	//QStandardItem *item2 = new QStandardItem("Item 2");
	//rootItem->appendRow(item2);

	//QStandardItem *childItem1 = new QStandardItem("Child Item 1");
	//item1->appendRow(childItem1);
	//QStandardItem *childItem2 = new QStandardItem("Child Item 2");
	//item1->appendRow(childItem2);

	//QColumnView* view = new QColumnView(mw);
	//view->setModel(&model);

	/** 4 QHeaderView */
	//// 创建数据模型
	//QStandardItemModel model;
	//model.setHorizontalHeaderLabels({"qt4.8","qt5.13","qt6.5"});

	//QHeaderView *headerView = new QHeaderView(Qt::Horizontal,mw);
	//headerView->setModel(&model);
	//headerView->resize(300, 20);

	//// 设置是否拉伸最后一列
	//headerView->setStretchLastSection(true);
	//// 设置默认列宽
	//headerView->setDefaultSectionSize(50);
	//


	///** 5 QListView */
	//// 创建数据模型
	//QStandardItemModel model;

	//// 添加图标项
	//QStandardItem *item1 = new QStandardItem(QIcon("../images/love.png"), "Item 1");
	//QStandardItem *item2 = new QStandardItem(QIcon("../images/love.png"), "Item 2");
	//QStandardItem *item3 = new QStandardItem(QIcon("../images/love.png"), "Item 3");
	//QStandardItem *item4 = new QStandardItem(QIcon("../images/love.png"), "Item 4");

	//// 添加项到数据模型
	//model.appendRow(item1);
	//model.appendRow(item2);
	//model.appendRow(item3);
	//model.appendRow(item4);

	//QListView* listView = new QListView(mw);
	//listView->setModel(&model);
	////listView->setViewMode(QListView::IconMode);
	////listView->setFlow(QListView::LeftToRight);

	///** 6 QUndoView */
	//QUndoView* undoView = new QUndoView(mw);
	//QUndoStack* undoStack = new QUndoStack(mw);
	//undoView->setStack(undoStack);

	//undoStack->push(new QUndoCommand("移动节点"));
	//undoStack->push(new QUndoCommand("添加连线"));
	//undoStack->push(new QUndoCommand("添加场景"));



	///** 7 QTableView */
	//// 创建数据模型
	//QStandardItemModel model;

	//// 设置表头
	//model.setHorizontalHeaderLabels({ "Name", "Age", "Country" });

	//// 添加数据
	//model.setItem(0, 0, new QStandardItem("John"));
	//model.setItem(0, 1, new QStandardItem("25"));
	//model.setItem(0, 2, new QStandardItem("USA"));

	//model.setItem(1, 0, new QStandardItem("Alice"));
	//model.setItem(1, 1, new QStandardItem("30"));
	//model.setItem(1, 2, new QStandardItem("Canada"));

	//QTableView* tableView = new QTableView(mw);
	//tableView->setModel(&model);

	////// 隐藏垂直header 
	////tableView->verticalHeader()->hide();
	////// 隐藏垂直grid 
	////tableView->setShowGrid(false);
	//// 设置按钮
	//tableView->setIndexWidget(model.index(1, 2), new QPushButton("(1,2)按钮"));



	///** 8 QTreeView */
	// // 创建数据模型
	//QStandardItemModel model;

	//// 添加根节点
	//QStandardItem *rootItem = model.invisibleRootItem();

	//// 添加子节点
	//QStandardItem *node1 = new QStandardItem("Node 1");
	//rootItem->appendRow(node1);

	//QStandardItem *node2 = new QStandardItem("Node 2");
	//rootItem->appendRow(node2);

	//// 添加孙子节点
	//QStandardItem *child1 = new QStandardItem("Child 1");
	//node1->appendRow(child1);

	//QStandardItem *child2 = new QStandardItem("Child 2");
	//node1->appendRow(child2);

	//QTreeView* treeView = new QTreeView(mw);
	//treeView->setModel(&model);

	//treeView->expandAll();
	//treeView->collapseAll();
	//treeView->setIndentation(10);
	//treeView->header()->hide();
	//treeView->header()->setStretchLastSection(true);


	/** 9 QGraphicsView */
	//QGraphicsView* graphicsView = new QGraphicsView(mw);

	/** 10 QChartView */
	//QChartView *view = new QChartView(mw);

	/** 11 QTextBrowser */
	//QTextBrowser* textBrowser = new QTextBrowser(mw);

	mw->show();
    return a.exec();
}

#include "main.moc"