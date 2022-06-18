#pragma once

#include <QUndoCommand>
#include <QGraphicsScene>

class lxQRemoveShapeCommand : public QUndoCommand
{

public:
	lxQRemoveShapeCommand(QGraphicsScene *_scene, QUndoCommand *parent=nullptr);

	void redo() override;
	void undo() override;
private:
	QGraphicsScene *mp_scene;
	QList<QGraphicsItem *> mlist_selectedItems;

};


