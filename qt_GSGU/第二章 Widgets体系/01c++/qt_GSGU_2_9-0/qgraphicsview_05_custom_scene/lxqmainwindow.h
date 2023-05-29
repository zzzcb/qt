#pragma once

#include <QMainWindow>

class lxQGraphicsView;
class lxQGraphicsScene;

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

	lxQGraphicsView*   m_pGraphicsView;
	lxQGraphicsScene*  m_pGraphisScene;
};
