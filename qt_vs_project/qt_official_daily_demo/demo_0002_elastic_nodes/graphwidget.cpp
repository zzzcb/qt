#include "graphwidget.h"
#include "node.h"
#include "edge.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QRandomGenerator>
#include <QDebug>


GraphWidget::GraphWidget(QWidget *parent)
	: QGraphicsView(parent),mTimerId(0)
{
	setMinimumSize(420, 420);
	QGraphicsScene* scene = new QGraphicsScene(this);

	scene->setSceneRect(-200, -200, 400, 400);
	scene->setItemIndexMethod(QGraphicsScene::NoIndex);
	setScene(scene);

	// view set up 
	setCacheMode(QGraphicsView::CacheBackground);
	setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
	setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
	setRenderHint(QPainter::Antialiasing);

	//scale(0.8, 0.8);

	// add node 
	Node* node1 = new Node(this);
	Node* node2 = new Node(this);
	Node* node3 = new Node(this);
	Node* node4 = new Node(this);
	mCenterNode = new Node(this);
	Node* node6 = new Node(this);
	Node* node7 = new Node(this);
	Node* node8 = new Node(this);
	Node* node9 = new Node(this);
	node1->setPos(-50, -50);
	node2->setPos(0, -50);
	node3->setPos(50, -50);
	node4->setPos(-50, 0);
	mCenterNode->setPos(0, 0);
	node6->setPos(50, 0);
	node7->setPos(-50, 50);
	node8->setPos(0, 50);
	node9->setPos(50, 50);

	mvNodes.push_back(mCenterNode);
	mvNodes.push_back(node1);
	mvNodes.push_back(node2);
	mvNodes.push_back(node3);
	mvNodes.push_back(node4);
	mvNodes.push_back(node6);
	mvNodes.push_back(node7);
	mvNodes.push_back(node8);
	mvNodes.push_back(node9);
	for (auto node : mvNodes)
		scene->addItem(node);


	// add edge 
	Edge* edge1 = new Edge(node1, node2);
	Edge* edge2 = new Edge(node1, node4);
	Edge* edge3 = new Edge(node2, node3);
	Edge* edge4 = new Edge(node2, mCenterNode);
	Edge* edge5 = new Edge(node3, node6);
	Edge* edge6 = new Edge(node4, mCenterNode);
	Edge* edge7 = new Edge(node4, node7);
	Edge* edge8 = new Edge(node6, mCenterNode);
	Edge* edge9 = new Edge(node6, node9);
	Edge* edge10 = new Edge(node7, node8);
	Edge* edge11 = new Edge(node8, mCenterNode);
	Edge* edge12 = new Edge(node8, node9);
	mvEdges.push_back(edge1);
	mvEdges.push_back(edge2);
	mvEdges.push_back(edge3);
	mvEdges.push_back(edge4);
	mvEdges.push_back(edge5);
	mvEdges.push_back(edge6);
	mvEdges.push_back(edge7);
	mvEdges.push_back(edge8);
	mvEdges.push_back(edge9);
	mvEdges.push_back(edge10);
	mvEdges.push_back(edge11);
	mvEdges.push_back(edge12);
	for (auto edge : mvEdges)
		scene->addItem(edge);
}

GraphWidget::~GraphWidget()
{
	for (auto node : mvNodes)
		delete node;

	for (auto edge : mvEdges)
		delete edge;
}

void GraphWidget::itemMoved()
{
	if (!mTimerId)
		mTimerId = startTimer(1000 / 25);
}

void GraphWidget::zoomIn()
{
	scaleView(qreal(1.2));
}

void GraphWidget::zoomOut()
{
	scaleView(qreal(0.8));
}

void GraphWidget::shuffle()
{
	qDebug() << "item size is " << scene()->items().size();

	for (auto item : scene()->items())
	{
		if (qgraphicsitem_cast<Node*>(item))
			item->setPos(-150+QRandomGenerator::global()->bounded(300),-150+QRandomGenerator::global()->bounded(300));
	}
}

void GraphWidget::drawBackground(QPainter *painter, const QRectF &rect)
{
	// shadow 
	QRectF sceneRct = sceneRect();
	QRectF rightShadow(sceneRct.right(), sceneRct.top() + 5, 5, sceneRct.height());
	QRectF bottomShadow(sceneRct.left() + 5, sceneRct.bottom(), sceneRct.width(), 5);

	painter->fillRect(rightShadow, Qt::darkGray);
	painter->fillRect(bottomShadow, Qt::darkGray);

	// fill color
	QLinearGradient gradient(sceneRct.topLeft(), sceneRct.bottomRight());
	gradient.setColorAt(0, Qt::white);
	gradient.setColorAt(1, Qt::lightGray);
	painter->fillRect(sceneRct, gradient);
	painter->drawRect(sceneRct);

	// text 
	QRectF textRct(sceneRct.left() + 4, sceneRct.top() + 4, sceneRct.width() - 8, sceneRct.height() - 8);
	QFont font = painter->font();
	font.setBold(true);
	font.setPointSize(14);
	
	QString msg(tr("Click and drag the nodes around, and zoom with the mouse "
		"wheel or the '+' and '-' keys"));

	painter->setFont(font);

	painter->setPen(Qt::lightGray);
	painter->drawText(textRct.translated(2,2), msg);
	
	painter->setPen(Qt::black);
	painter->drawText(textRct, msg);


	//qDebug() << "back rect " << rect;
	//qDebug() << "sceneRct rect " << sceneRct;



}

void GraphWidget::wheelEvent(QWheelEvent *event)
{
	scaleView(std::pow(2,event->delta()/240.0));
}

void GraphWidget::keyPressEvent(QKeyEvent *event)
{
	switch (event->key())
	{
	case Qt::Key_Up:
		mCenterNode->moveBy(0, -20);
		break;
	case Qt::Key_Down:
		mCenterNode->moveBy(0, 20);
		break;
	case Qt::Key_Left:
		mCenterNode->moveBy(-20, 0);
		break;
	case Qt::Key_Right:
		mCenterNode->moveBy(20, 0);
		break;
	case Qt::Key_Plus:
		zoomIn();
		break;
	case Qt::Key_Minus:
		zoomOut();
		break;
	case Qt::Key_Space:
	case Qt::Key_Enter:
		shuffle();
		break;
	default:
		break;
	}

}

void GraphWidget::timerEvent(QTimerEvent *event)
{
	QList<Node*> listNode;
	for (auto item : scene()->items())
		if (Node* node=qgraphicsitem_cast<Node*>(item))
			listNode << node;

	for (auto node : listNode)
		node->calcForces();

	bool updatedNodePos = false;
	// 遍历所有node查看是否有node需要更新位置
	for (auto node : listNode)
		if (node->advancePos())
			updatedNodePos = true;

	if (!updatedNodePos)
	{
		killTimer(mTimerId);
		mTimerId = 0;
	}
}

void GraphWidget::scaleView(qreal scaleFactor)
{
	qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
	
	if (factor < 0.07 || factor > 100)
		return;

	scale(scaleFactor, scaleFactor);
}

