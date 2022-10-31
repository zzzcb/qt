/**
  ******************************************************************************
  * @file		lxqundocommands.h
  * @author		LinxZCB
  * @version	V1.0.0
  * @date		2022.10.27
  * @brief		基于Qt Undo Framework 的回退操作
					主要分为三种回退:1,新增node回退 2,移动node回退 3,删除node回退
					对于曲线,暂时不支持回退,删除node即将曲线干掉,回退node也不恢复曲线的连接
					lxQAddNodeCommand 在拖入node的时候触发,由view里发射出信号
					lxQMoveNodeCommand 在移动的时候触发,由scene里发射出信号,widget连接到这个信号进而将command 放入到undostack中 
					lxQDeleteNodeCommand 在按下delete快捷键时触发
					快捷键:ctrl+z 回退  ctrl+shift+z 恢复回退
  * @details
  * @copyright  Copyright (c) 2018-2022 杭州灵西机器人智能科技有限公司
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
*/
#pragma once

#include <QUndoCommand>
#include <QGraphicsScene>

class lxQAddNodeCommand : public QUndoCommand
{
public:
	lxQAddNodeCommand(QGraphicsItem *item, QGraphicsScene *scene,QUndoCommand *parent = nullptr);
	~lxQAddNodeCommand();

	void redo() override;
	void undo() override;

private:
	QGraphicsItem *m_pItem;     ///< 新增的item
	QGraphicsScene *m_pScene;	///< 场景
	QPointF m_tInitPos;			///< 初始位置

	bool    m_bRedo=true;		///< 是否处于redo状态,如果是的话，就是在scene里面管理，析构时就不用删除item了
};


class lxQMoveNodeCommand : public QUndoCommand
{
public:
	lxQMoveNodeCommand(QGraphicsScene *scene, const QPointF & offset, QUndoCommand *parent = nullptr);

	void redo() override;
	void undo() override;

private:
	bool m_bInit = true;				///< 是否为初始状态 

	QGraphicsScene *m_pScene;			///< 场景
	QList<QGraphicsItem*> m_listItem;   ///< items 
	QPointF m_tMoveOffset;				///< item 相对之前位置移动的距离
};

class lxQDeleteNodeCommand : public QUndoCommand
{

public:
	lxQDeleteNodeCommand(QGraphicsScene *scene, QUndoCommand *parent = nullptr);

	void redo() override;				
	void undo() override;
private:
	QGraphicsScene *m_pScene;
	QList<QGraphicsItem *> m_listItem;
};
