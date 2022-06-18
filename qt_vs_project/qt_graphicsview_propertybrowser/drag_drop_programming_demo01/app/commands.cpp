#include "commands.h"

#include <QGraphicsItem>

#include <QDebug>

lxQRemoveShapeCommand::lxQRemoveShapeCommand(QGraphicsScene *_scene,QUndoCommand *parent/*=nullptr*/)
	:QUndoCommand(parent)
{
	mp_scene = _scene;
	mlist_selectedItems = _scene->selectedItems();
}

void lxQRemoveShapeCommand::redo()
{
	for (auto item : mlist_selectedItems)
	{
		mp_scene->removeItem(item);
	}
	setText(QObject::tr("Redo Delete %1").arg(mlist_selectedItems.count()));
}

void lxQRemoveShapeCommand::undo()
{
	for (auto item : mlist_selectedItems)
	{
		mp_scene->addItem(item);
	}
	mp_scene->update();
	setText(QObject::tr("Undo Delete %1").arg(mlist_selectedItems.count()));
}
