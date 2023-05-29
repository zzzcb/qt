#pragma once

#include <QWidget>
#include <QAction>
#include <QUndoStack>
#include "ui_lxdragdropwidget.h"


class lxQDragDropWidget : public QWidget
{
	Q_OBJECT

public:
	lxQDragDropWidget(QWidget *parent = Q_NULLPTR);
	~lxQDragDropWidget();

private slots:

	
	void slot_itemAdded(QGraphicsItem *item, QGraphicsScene *scene);
	void slot_itemMoved(QGraphicsScene* scene, const QPointF& offset);
	void slot_itemDelete();


private:
	Ui::LxDragDropWidget ui;

	// action 
	QAction* mpDeleteAct;
	QAction* mpRedoAct;
	QAction* mpUndoAct;



	QUndoStack* mpUndoStack;


};
