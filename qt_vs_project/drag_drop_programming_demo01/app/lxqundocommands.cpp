#include "lxqundocommands.h"

#include <QGraphicsItem>

#include <QDebug>


/**============ add node ============*/

lxQAddNodeCommand::lxQAddNodeCommand(QGraphicsItem *item, QGraphicsScene *scene, QUndoCommand *parent /*= nullptr*/)
	: QUndoCommand(parent)
{
	m_pItem = item;
	m_pScene = scene;
	m_tInitPos = item->scenePos();
}

lxQAddNodeCommand::~lxQAddNodeCommand()
{ 
	if (!m_bRedo && m_pItem && !m_pItem->scene())
		delete m_pItem;
}


void lxQAddNodeCommand::redo()
{
	m_bRedo = true;

	m_pItem->setPos(m_tInitPos);
	if (m_pItem->scene() == nullptr)
		m_pScene->addItem(m_pItem);

	m_pScene->update();

	setText(QObject::tr("Redo Add %1,%2")
		.arg(m_tInitPos.x()).arg(m_tInitPos.y()));
}

void lxQAddNodeCommand::undo()
{
	m_bRedo = false;

	m_pScene->removeItem(m_pItem);
	m_pScene->update();

	setText(QObject::tr("Undo Add %1,%2")
		.arg(m_tInitPos.x()).arg(m_tInitPos.y()));
}
/**============ move node command ============*/
lxQMoveNodeCommand::lxQMoveNodeCommand(QGraphicsScene *scene, const QPointF & offset, QUndoCommand *parent /*= nullptr*/)
	: QUndoCommand(parent)
{
	m_pScene = scene;
	m_tMoveOffset = offset;

	for (auto item : scene->selectedItems())
	{
		if (item->parentItem()) // viz item,not body item 
		{
			m_listItem.push_back(item->parentItem());
		}
	}
}

void lxQMoveNodeCommand::redo()
{
	if (!m_bInit)
	{
		for (auto item : m_listItem)
		{
			item->moveBy(m_tMoveOffset.x(), m_tMoveOffset.y());
		}
		m_pScene->update();

	}
	setText(QObject::tr("Redo Move %1,%2")
		.arg(m_tMoveOffset.x()).arg(m_tMoveOffset.y()));
}

void lxQMoveNodeCommand::undo()
{
	for (auto item : m_listItem)
	{
		item->moveBy(-m_tMoveOffset.x(), -m_tMoveOffset.y());
	}
	m_pScene->update();

	setText(QObject::tr("Undo Move %1,%2")
		.arg(-m_tMoveOffset.x()).arg(-m_tMoveOffset.y()));
	m_bInit = false;
}


/**============ delete node command ============*/

lxQDeleteNodeCommand::lxQDeleteNodeCommand(QGraphicsScene *scene, QUndoCommand *parent/*=nullptr*/)
	:QUndoCommand(parent)
{
	m_pScene = scene;
	for (auto item : scene->selectedItems())
	{
		if (item->parentItem()) // viz item,not body item 
		{
			m_listItem.push_back(item->parentItem());
		}
	}
}

void lxQDeleteNodeCommand::redo()
{
	for (auto item : m_listItem)
	{
		m_pScene->removeItem(item);
	}
	m_pScene->update();
	setText(QObject::tr("Redo Delete %1").arg(m_listItem.count()));
}

void lxQDeleteNodeCommand::undo()
{
	for (auto item : m_listItem)
	{
		m_pScene->addItem(item);
	}
	m_pScene->update();
	setText(QObject::tr("Undo Delete %1").arg(m_listItem.count()));
}