#pragma once

#include <QDialog>
#include "ui_vs2017_solution.h"

#include <QStandardItemModel>

enum CustomRole
{
	TYPE = Qt::UserRole+1,  // 类别角色
	DESC,					// 描述角色
};

enum RobotScene
{
	DEPTZ = 10, // 拆垛
	PTZ,		// 码垛
	PICK,		// 工业拣选
	CUSTOM		// 自定义
};

class VS2017SolutionMng : public QDialog
{
	Q_OBJECT

public:
	VS2017SolutionMng(QWidget *parent = nullptr);
	~VS2017SolutionMng();

private slots:
	void slot_treeItemPressed(const QModelIndex &index);
	void slot_listItemPressed(const QModelIndex &index);

private:
	void initModel();

	void setupTreeView();
	void setupListView();
	void setupActions();
	void updateDescInfo(QString type,QString detail);
	
	Ui::VS2017SolutionMngClass ui;

	QStandardItemModel* m_pTreeItemModel;
	QStandardItemModel* m_pListItemModel;  // 全部的list 
	QStandardItemModel* m_pListShowModel;  // 当前展示的list 

	QModelIndex m_tCurTreeIndex;           // 当前选中的tree item 
};

