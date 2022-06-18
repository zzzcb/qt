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
	void on_deleteAct_triggered();


private:
	Ui::LxDragDropWidget ui;

	// action 
	QAction* mpDeleteAct;
	QAction* mpRedoAct;
	QAction* mpUndoAct;



	QUndoStack* mpUndoStack;


};
