#include "lxqundoview.h"
#include <QDebug>
#include <QMouseEvent>

lxQUndoView::lxQUndoView(QWidget *parent)
	:QUndoView(parent)
{
	//setStyleSheet("background-color:rgb(38,38,38);\nborder:no border;");
}

lxQUndoView::~lxQUndoView()
{

}

void lxQUndoView::mousePressEvent(QMouseEvent *event)
{
	event->accept();  ///<  重写鼠标事件 使鼠标事件不往下传递 以达到不能通过鼠标来触发redo/undo的目的
}

void lxQUndoView::mouseMoveEvent(QMouseEvent *event)
{
	event->accept();  ///<  重写鼠标事件 使鼠标事件不往下传递 以达到不能通过鼠标来触发redo/undo的目的
}
