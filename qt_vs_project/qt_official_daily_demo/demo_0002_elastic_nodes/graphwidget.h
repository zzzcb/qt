#pragma once

#include <QGraphicsView>
#include <QPushButton>
#include <QVector>

class Node;
class Edge;

class GraphWidget : public QGraphicsView
{
	Q_OBJECT

public:
	GraphWidget(QWidget *parent=nullptr);
	~GraphWidget();
	
	void itemMoved();

public slots:
	void zoomIn();
	void zoomOut();
	void shuffle();

protected:
	void drawBackground(QPainter *painter, const QRectF &rect) override;
	void wheelEvent(QWheelEvent *event) override;
	void keyPressEvent(QKeyEvent *event) override;
	void timerEvent(QTimerEvent *event) override;

private:
	void scaleView(qreal scaleFactor);

	int mTimerId;
	Node * mCenterNode;

	QVector<Node*> mvNodes;
	QVector<Edge*> mvEdges;


	QPushButton* mpBtn;

private slots:
	void on_mpBtn_clicked();
};
