#include "lxqdragdropwidget.h"

#include "commands.h"
#include <QTreeWidgetItem>
#include <QDebug>

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
	connect(mpDeleteAct, &QAction::triggered, this, &lxQDragDropWidget::on_deleteAct_triggered);

	mpRedoAct = mpUndoStack->createRedoAction(this, tr("redo"));
	mpRedoAct->setShortcuts(QKeySequence::Redo);

	mpUndoAct = mpUndoStack->createUndoAction(this, tr("undo"));
	mpUndoAct->setShortcuts(QKeySequence::Undo);

	this->addAction(mpDeleteAct);
	this->addAction(mpRedoAct);
	this->addAction(mpUndoAct);
}

lxQDragDropWidget::~lxQDragDropWidget()
{

}

void lxQDragDropWidget::on_deleteAct_triggered()
{
	QGraphicsScene* scene = ui.graphicsView->scene();
	if (scene->selectedItems().isEmpty())
		return;
	

	QUndoCommand *deleteCommand = new lxQRemoveShapeCommand(scene);
	mpUndoStack->push(deleteCommand);
}
