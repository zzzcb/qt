#pragma once

#include <QMainWindow>

class QGraphicsView;
class QGraphicsScene;

class lxQMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	lxQMainWindow(QWidget *parent = nullptr);
	~lxQMainWindow();

protected:
	void mouseDoubleClickEvent(QMouseEvent *event) override;

private:
	void initQSS();

	QGraphicsView*   m_pGraphicsView;
	QGraphicsScene*  m_pGraphisScene;
};
