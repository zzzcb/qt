#pragma once

#include <QWidget>
#include <QAction>
#include <QUndoStack>
#include "ui_lxdragdropwidget.h"

class LxDragDropWidget : public QWidget
{
	Q_OBJECT

public:
	LxDragDropWidget(QWidget *parent = Q_NULLPTR);
	~LxDragDropWidget();

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
