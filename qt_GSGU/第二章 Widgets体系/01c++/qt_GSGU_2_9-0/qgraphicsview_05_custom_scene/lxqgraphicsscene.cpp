#pragma execution_character_set("utf-8")
#include "lxqgraphicsscene.h"
#include "lxqgraphicsitem.h"

#include <QApplication>
#include <QClipboard>
#include <QMimeData>
#include <QKeyEvent>
#include <QPainter>
#include <QMessageBox>

lxQGraphicsScene::lxQGraphicsScene(const QRectF &sceneRect, QObject *parent)
	:QGraphicsScene(sceneRect, parent)
{

}

void lxQGraphicsScene::drawBackground(QPainter *painter, const QRectF &rect)
{
	QGraphicsScene::drawBackground(painter, rect);

	painter->setPen(Qt::red);
	painter->drawLine(QPointF(0, 0), QPointF(20, 0));  // x axis 
	painter->setPen(Qt::green);
	painter->drawLine(QPointF(0, 0), QPointF(0, 20));  // y axis 
}

void lxQGraphicsScene::deleteSelectedItems()
{
	if (selectedItems().isEmpty())
		return;
	else
	{
		QList<QGraphicsItem*> vNoParent;
		for (auto item : selectedItems())
		{
			if (!item->parentItem())
			{
				vNoParent.push_back(item);
			}
		}
		
		/**需要在此统一删除,不然会有bug*/
		for (auto item : vNoParent)
		{
			removeItem(item);
			delete item;
		}
		
		/**清理下剪切板*/
		QApplication::clipboard()->clear();
		
		update();
	}
}

void lxQGraphicsScene::copySelectedItem()
{
	QApplication::clipboard()->clear();
	QApplication::clipboard()->setMimeData(new lxQGraphicsMimeData(selectedItems()));
}

void lxQGraphicsScene::pasteItem()
{
	/** const_cast转换符是用来移除变量的const限定符*/
	QMimeData* md = const_cast<QMimeData*>(QApplication::clipboard()->mimeData());
	lxQGraphicsMimeData* data = dynamic_cast<lxQGraphicsMimeData*>(md);
	if (data)
	{
		clearSelection();
		/** ctrl + v 将剪切板的item再复制一份加入到scene中*/
		for (const auto&item : data->getItems())
		{
			auto _item = qgraphicsitem_cast<lxQGraphicsPixmapItem*>(item);
			if (_item)
			{
				auto copy = _item->duplicate();
				copy->setSelected(true);
				addItem(copy);
				copy->moveBy(10, 10);
			}
		}

		/** 更新剪切板中的内容*/
		QApplication::clipboard()->setMimeData(new lxQGraphicsMimeData(selectedItems()));
	}
	else
	{
		QMessageBox::information(nullptr, "剪切板为空", "需要先进行复制才可以粘贴");
	}
}

void lxQGraphicsScene::keyPressEvent(QKeyEvent *event)
{
	switch (event->key())
	{
	case Qt::Key_Delete:
		deleteSelectedItems();
		break;
	case Qt::Key_C:
		copySelectedItem();
		break;
	case Qt::Key_V:
		pasteItem();
		break;
	default:
		break;
	}

	update();

	QGraphicsScene::keyPressEvent(event);
}
