#pragma once

#include <QMainWindow>

class QPushButton;
class QComboBox;
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

	QGraphicsView* m_pGraphicsView;
	QList<QGraphicsScene*> m_listGraphicsScene;

	QPushButton* m_pAddViewBtn;
	QPushButton* m_pAddSceneBtn;
	QPushButton* m_pClearItemBtn;
	QComboBox*   m_pSwitchSceneBtn;


private slots:
	void slot_toolBtn_handle(int data);
};
