#pragma once

#include <QGraphicsScene>
#include <QMimeData>

class lxQGraphicsScene : public QGraphicsScene
{
	Q_OBJECT
public:
	lxQGraphicsScene(const QRectF &sceneRect, QObject *parent = nullptr);

protected:
	void drawBackground(QPainter *painter, const QRectF &rect) override;

private:
	void deleteSelectedItems();
	void copySelectedItem();
	void pasteItem();

	void keyPressEvent(QKeyEvent *event) override;
};
