#include "lxqdragdropwidget.h"
#include "lxqgraphicsscene.h"

#include "lxqundocommands.h"
#include <QTreeWidgetItem>
#include <QGraphicsItem>
#include <QDebug>

class MyUndoStack :public QUndoStack
{
public:
	MyUndoStack(QObject* parent=nullptr)
		:QUndoStack(parent)
	{
	}
};





lxQDragDropWidget::lxQDragDropWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	
	ui.splitter_2->setSizes(QList<int>({ 1,200 }));
	ui.splitter_3->setSizes(QList<int>({ 1,1 }));


	mpUndoStack = new QUndoStack(this);
	ui.undoView->setStack(mpUndoStack);

	/**action*/
	mpDeleteAct = new QAction(tr("&Delete"), this);
	mpDeleteAct->setShortcut(QKeySequence::Delete);

	// 连接undo 相关的信号槽  
	connect(ui.graphicsView, &lxQGraphicsView::signal_itemAdded, this, &lxQDragDropWidget::slot_itemAdded);
	connect(ui.graphicsView->m_pScene, &lxQGraphicsScene::signal_itemMoved, this, &lxQDragDropWidget::slot_itemMoved);
	connect(mpDeleteAct, &QAction::triggered, this, &lxQDragDropWidget::slot_itemDelete);

	mpRedoAct = mpUndoStack->createRedoAction(this, tr("redo"));
	mpRedoAct->setShortcuts(QKeySequence::Redo);

	mpUndoAct = mpUndoStack->createUndoAction(this, tr("undo"));
	mpUndoAct->setShortcuts(QKeySequence::Undo);

	addAction(mpDeleteAct);
	addAction(mpRedoAct);
	addAction(mpUndoAct);

}

lxQDragDropWidget::~lxQDragDropWidget()
{

}


void lxQDragDropWidget::slot_itemAdded(QGraphicsItem *item, QGraphicsScene *scene)
{
	qDebug() << item << "  " << scene;

	mpUndoStack->push(new lxQAddNodeCommand(item,scene));
}

void lxQDragDropWidget::slot_itemMoved(QGraphicsScene* scene, const QPointF& offset)
{
	qDebug() << scene<< "  " << offset;

	mpUndoStack->push(new lxQMoveNodeCommand(scene,offset));
}

void lxQDragDropWidget::slot_itemDelete()
{
	QGraphicsScene* scene = ui.graphicsView->scene();
	if (scene->selectedItems().isEmpty())
		return;

	mpUndoStack->push(new lxQDeleteNodeCommand(scene));
}