#pragma once

#include <QMainWindow>
#include <QPainterPath>

class QPushButton;
class QComboBox;
class QGraphicsView;
class QGraphicsScene;
class QDialog;
class QFormLayout;


class lxQMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	lxQMainWindow(QWidget *parent = nullptr);
	~lxQMainWindow();

private:
	void initQSS();
	void initItemTypeComboBox();
	void initConfigPanel();
	void resetConfigPanel();

	bool eventFilter(QObject *watched, QEvent *event) override;

	QGraphicsView*   m_pGraphicsView;
	QGraphicsScene*  m_pGraphicsScene;

	QPushButton*     m_pAddItemBtn;
	QPushButton*     m_pClearSceneBtn;
	QComboBox*       m_pItemTypeBtn;
				     
	QDialog*	     m_pConfigPanel;
	QFormLayout*     m_pFormLayout;
	QWidget*	     m_pCollectPointPanel;
	QVector<QPointF> m_vPoints;
	QPainterPath     m_tPainterPath;

private slots:
	void slot_toolBtn_handle(int data);
};
