#pragma execution_character_set("utf-8")
#include "vs2017_solution.h"

#include <QMouseEvent>
#include <QDebug>


QString DESC_TEMPLATE = QString("<h3>类型: %1</h3><p>%2</p>");

VS2017SolutionMng::VS2017SolutionMng(QWidget *parent)
	: QDialog(parent)
{
	QFile file(":/vs2017_solution.qss");
	if (file.open(QIODevice::ReadOnly))
	{
		setStyleSheet(file.readAll());
	}

	ui.setupUi(this);
	setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowContextHelpButtonHint | Qt::WindowCloseButtonHint);
	resize(1000, 560);

	initModel();
	setupTreeView();
	setupListView();
	setupActions();

	// disable text browser selection
	ui.textBrowser->setTextInteractionFlags(Qt::NoTextInteraction);

	// default select tree first item
	QModelIndex rootIdx = m_pTreeItemModel->index(0, 0);
	QModelIndex firstTreeIdx = m_pTreeItemModel->index(0, 0, rootIdx);
	ui.treeView->setCurrentIndex(firstTreeIdx);
	slot_treeItemPressed(firstTreeIdx);

	// default select list first item 
	QModelIndex firstListIdx = m_pListShowModel->index(0, 0);
	ui.listView->setCurrentIndex(firstListIdx);
	slot_listItemPressed(firstListIdx);
}

VS2017SolutionMng::~VS2017SolutionMng()
{

}

void VS2017SolutionMng::slot_treeItemPressed(const QModelIndex &index)
{
	// update list view
	m_pListShowModel->clear();

	for (int i = 0; i < m_pListItemModel->rowCount(); i++)
	{
		QModelIndex iIdx =  m_pListItemModel->index(i, 0);
		auto item =  m_pListItemModel->itemFromIndex(iIdx);
		if (item->data(CustomRole::TYPE).toInt() == index.data(CustomRole::TYPE).toInt())
		{
			auto newItem = new QStandardItem(item->icon(), item->text());
			newItem->setData(item->data(CustomRole::DESC), CustomRole::DESC);
			m_pListShowModel->appendRow(newItem);
		}
	}

	m_tCurTreeIndex = index;

	// default select list first item 
	QModelIndex firstListIdx = m_pListShowModel->index(0, 0);
	ui.listView->setCurrentIndex(firstListIdx);
	slot_listItemPressed(firstListIdx);
}

void VS2017SolutionMng::slot_listItemPressed(const QModelIndex &index)
{
	// update browser info 

	if (!index.isValid())
		updateDescInfo("None", "");
	else
		updateDescInfo(m_tCurTreeIndex.data(CustomRole::DESC).toString(),index.data(CustomRole::DESC).toString());
}

void VS2017SolutionMng::initModel()
{
	m_pTreeItemModel = new QStandardItemModel(this);
	m_pListItemModel = new QStandardItemModel(this);
	m_pListShowModel = new QStandardItemModel(this);

	// item
	QStandardItem* root = new QStandardItem("已安装"); 

	QStandardItem* deptzType = new QStandardItem("标准拆垛"); 
	QStandardItem* singleDeptz = new QStandardItem(QIcon(":/images/deptz_single.png"), " 单一SKU拆垛");
	QStandardItem* mixDeptz = new QStandardItem(QIcon(":/images/deptz_mix.png"), " 混合SKU拆垛");

	QStandardItem* ptzType = new QStandardItem("标准码垛");
	QStandardItem* singlePtz = new QStandardItem(QIcon(":/images/ptz_single.png"), " 单一SKU码垛");
	QStandardItem* mixPtz = new QStandardItem(QIcon(":/images/ptz_mix.png"), " 混合SKU码垛");

	QStandardItem* pickType = new QStandardItem("工业拣选"); 
	QStandardItem* pick1 = new QStandardItem(QIcon(":/images/binpicking.png"), "截齿抓取");

	QStandardItem* cusType = new QStandardItem("自定义"); 
	QStandardItem* custom1 = new QStandardItem(QIcon(":/images/special_template.png"), "特殊模板");


	// 通过setData,使 tree 和 list 产生关联
	deptzType->setData(RobotScene::DEPTZ, CustomRole::TYPE);
	deptzType->setData("标准拆垛", CustomRole::DESC);
	singleDeptz->setData(RobotScene::DEPTZ, CustomRole::TYPE);
	singleDeptz->setData("拆垛是一个动词，对应的是堆垛。通俗的解释就是把推成一堆的物料一份一份的拆分开。", CustomRole::DESC);
	mixDeptz->setData(RobotScene::DEPTZ, CustomRole::TYPE);
	mixDeptz->setData("混拆是指从不同类型的sku中............", CustomRole::DESC);

	ptzType->setData(RobotScene::PTZ, CustomRole::TYPE);
	ptzType->setData("标准码垛", CustomRole::DESC);
	singlePtz->setData(RobotScene::PTZ, CustomRole::TYPE);
	singlePtz->setData("发的首付款理解啊砥砺奋进阿里法司法局富士达李逵负荆发拉动经济", CustomRole::DESC);
	mixPtz->setData(RobotScene::PTZ, CustomRole::TYPE);
	mixPtz->setData("混的书法家阿来得及发酵的发送方建安的说法林俊杰附件阿里的司法局", CustomRole::DESC);
	
	pickType->setData(RobotScene::PICK, CustomRole::TYPE);
	pickType->setData("工业拣选", CustomRole::DESC);
	pick1->setData(RobotScene::PICK, CustomRole::TYPE);
	pick1->setData("截齿拣选,是指将截齿抓的富士康两地分居水电费拉对方就dslf都结束了附近.", CustomRole::DESC);

	cusType->setData(RobotScene::CUSTOM, CustomRole::TYPE);
	cusType->setData("自定义", CustomRole::DESC);
	custom1->setData(RobotScene::CUSTOM, CustomRole::TYPE);
	custom1->setData("用户可以按照自己的想法进行拖拽式编程。。。。。。。。", CustomRole::DESC);

	// 构建 模型
	m_pTreeItemModel->appendRow({ root });
	root->appendRows({ deptzType,ptzType,pickType,cusType });
	for (auto item : { singleDeptz,mixDeptz,singlePtz,mixPtz,pick1,custom1 })
		m_pListItemModel->appendRow(item);

}

void VS2017SolutionMng::setupTreeView()
{
	ui.treeView->setHeaderHidden(true);
	ui.treeView->setIndentation(12);
	ui.treeView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui.treeView->setModel(m_pTreeItemModel);

	connect(ui.treeView, &QTreeView::pressed, this, &VS2017SolutionMng::slot_treeItemPressed);
}

void VS2017SolutionMng::setupListView()
{
	ui.listView->setModel(m_pListShowModel);
	ui.listView->setEditTriggers(QAbstractItemView::NoEditTriggers);

	connect(ui.listView, &QListView::pressed, this, &VS2017SolutionMng::slot_listItemPressed);
}

void VS2017SolutionMng::setupActions()
{
	connect(ui.cancelBtn, &QPushButton::clicked, this, &QWidget::close);
}

void VS2017SolutionMng::updateDescInfo(QString type, QString detail)
{	
	ui.textBrowser->clear();

	ui.textBrowser->setHtml(DESC_TEMPLATE.arg(type, detail));
}

