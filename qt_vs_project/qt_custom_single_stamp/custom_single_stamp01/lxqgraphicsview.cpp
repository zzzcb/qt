#pragma execution_character_set("utf-8")
#include "lxqgraphicsview.h"
#include "lxqgraphicsscene.h"
#include "lxqgraphicsitem.h"

#include "lxqadddialog.h"
#include "lxqbuttongroup.h"

#include <QDebug>
#include <QApplication>
#include <QClipboard>
#include <QMimeData>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QFileDialog>
#include <QtMath>

lxQGraphicsView::lxQGraphicsView(QWidget *parent)
	: QGraphicsView(parent)
{
	/**给该view设置scene*/
	lxQGraphicsScene* scene = new lxQGraphicsScene(this);
	scene->setSceneRect(-400, -300, 800, 600);
	setScene(scene);

	/**给该view设置 自定义的按钮组 */
	mt_btnGroup = new lxQButtonGroup(this);
	mt_btnGroup->setButtonsDir(false);       ///< 垂直方向 
	mt_btnGroup->setButtonSize(45, 45);
	QVector<QString> vTmpPath = { ":/004_png_sources/robot.png",":/004_png_sources/robot.png",":/004_png_sources/robot.png",":/004_png_sources/robot.png",":/004_png_sources/robot.png" ,":/004_png_sources/robot.png"  };
	QVector<QString> vToolTip = { "托盘\n  拖拽以新增","箱子\n  拖拽以新增","桶子\n  拖拽以新增","麻袋\n  拖拽以新增","移动工具\n  点击以操作","旋转工具\n  点击以操作" };
	for (int i = 0; i < 6; i++)
	{
		if(i == 4 || i == 5)
			mt_btnGroup->addButton(vTmpPath[i],vToolTip[i],true);
		else 
			mt_btnGroup->addButton(vTmpPath[i],vToolTip[i],false,true);
	}
	mt_btnGroup->move(10, 50);
	
	/**设置scene的背景色为gray,此时会填满整个 view，可以通过重写scene的drawbackgroud来标识scene*/
	//scene->setBackgroundBrush(Qt::darkGray);

	setStyleSheet("background-color:rgb(57,57,57);");
	setAcceptDrops(true);
	setRenderHint(QPainter::Antialiasing);
	setTransformationAnchor(QGraphicsView::NoAnchor);
	/**默认支持橡皮筋选中*/
	setDragMode(QGraphicsView::RubberBandDrag);
}

lxQGraphicsView::~lxQGraphicsView()
{
}

void lxQGraphicsView::dragEnterEvent(QDragEnterEvent *event)
{
	event->setAccepted(true);

	QGraphicsView::dragEnterEvent(event);
}

void lxQGraphicsView::dragMoveEvent(QDragMoveEvent *event)
{
	/** 注意:好像必须要覆盖父类的dragMoveEvent方法,不然没法正常工作*/
}

void lxQGraphicsView::dropEvent(QDropEvent *event)
{
	auto mimeData = event->mimeData();

	if (!mimeData->hasText())
		return;

	/** 自定义基于Model-View的添加数据编辑框*/
	lxQAddDialog addDialog;
	addDialog.move(mapToGlobal(event->pos()));

	QPointF itemPos = mapToScene(event->pos());
	QString text = mimeData->text();
	if (text == "btn-0")
	{
		addDialog.initEditor("新增托盘",{ {"托盘长(mm)","QLineEdit","1000"}, {"托盘宽(mm)","QLineEdit","1000"},{"托盘角度(degree)","QLineEdit","0"} });
		if (addDialog.exec())
		{
			auto vRes = addDialog.getEditorResult();
			auto pallet = new lxQGraphicsPalletItem(vRes[0].toDouble(), vRes[1].toDouble());
			qDebug() << "cur pallet " << pallet;
			pallet->rotateAngle(vRes[2].toDouble());
			pallet->setPos(itemPos);
			scene()->addItem(pallet);
		}
	}
	else if (text == "btn-1")
	{
		addDialog.initEditor("新增箱子",{ {"箱子长(mm)","QLineEdit","100"}, {"箱子宽(mm)","QLineEdit","100"},{"箱子角度(degree)","QLineEdit","0"} });
		if (addDialog.exec())
		{
			auto vRes = addDialog.getEditorResult();
			auto box = new lxQGraphicsBoxItem(vRes[0].toDouble(),vRes[1].toDouble());
			box->rotateAngle(vRes[2].toDouble());
			box->setPos(itemPos);
			scene()->addItem(box);
		}
	}
	else if (text == "btn-2")
	{
		addDialog.initEditor("新增桶子",{ {"桶形直径(mm)","QLineEdit","100"} });
		if (addDialog.exec())
		{
			auto vRes = addDialog.getEditorResult();
			auto bucket = new lxQGraphicsBucketItem(vRes[0].toDouble());
			bucket->setPos(itemPos);
			scene()->addItem(bucket);
		}
	}
	else if (text == "btn-3")
	{
		addDialog.initEditor("新增麻袋",{ {"麻袋长(mm)","QLineEdit","100"}, {"麻袋宽(mm)","QLineEdit","50"} });
		if (addDialog.exec())
		{
			// TODO 
		}
	}
}

void lxQGraphicsView::keyPressEvent(QKeyEvent *event)
{
	auto deleteSelectItems = [](QGraphicsScene* scene)
	{
		if (scene->selectedItems().isEmpty())
			return;
		else
		{
			for (const auto& item : scene->selectedItems())
				scene->removeItem(item);
		}
	};

	auto attachToPallet = [](QGraphicsScene* scene) 
	{
		QGraphicsItem* parent = nullptr;
		for (auto &item : scene->selectedItems())
		{

			if (qgraphicsitem_cast<lxQGraphicsPalletItem*>(item))
			{
				parent = item;
				break;
			}
		}

		for (auto &item : scene->selectedItems())
		{
			if (qgraphicsitem_cast<lxQGraphicsPalletItem*>(item))
			{
				continue;
			}
			else
			{
				auto newPos = parent->mapFromScene(item->scenePos());

				item->setParentItem(parent);
				item->resetTransform();
				item->setPos(newPos);
			}
		}
	};

	auto detachFromPallet = [](QGraphicsScene* scene) 
	{
		for (auto &item : scene->selectedItems())
		{
			if (item->parentItem())
			{
				auto newPos = item->scenePos();

				item->setParentItem(nullptr);
				//item->resetTransform();
				item->setPos(newPos);


			}

		}
	};

	auto loadPallet = [this](QGraphicsScene* scene)
	{
		QString fileName = QFileDialog::getOpenFileName(this);
		if (!fileName.isEmpty())
		{
			QFile file(fileName);
			if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
			{
				return;
			}

			QJsonParseError err;
			QJsonDocument jDoc = QJsonDocument::fromJson(file.readAll(), &err);
			if (err.error != QJsonParseError::NoError)
				return;

			if (!jDoc.isObject())
				return;

			qreal L = 0, W = 0;
			qreal l = 0, w = 0, r = 0;
			qreal x = 0, y = 0, rz = 0;
			bool bBucket = false;

			auto jObj = jDoc.object();
			L = jObj["tierL"].toDouble();
			W = jObj["tierW"].toDouble();
			auto pallet = new lxQGraphicsPalletItem(L, W);
			scene->addItem(pallet);

			for (auto jTemp : jObj["units"].toArray())
			{
				auto jItem = jTemp.toObject();
				bBucket = jItem["bBucket"].toBool();
				if (bBucket)
				{
					r = jItem["r"].toDouble();
					x = jItem["x"].toDouble()/mm2PixelRatio;
					y = jItem["y"].toDouble()/mm2PixelRatio;
					auto bucket = new lxQGraphicsBucketItem(2 * r, pallet);
					bucket->setPos(x, y);
					scene->addItem(bucket);
				}
				else
				{
					l = jItem["l"].toDouble() ;
					w = jItem["w"].toDouble() ;
					x = jItem["x"].toDouble() /mm2PixelRatio;
					y = jItem["y"].toDouble() /mm2PixelRatio;
					rz = jItem["rz"].toDouble();
					auto box = new lxQGraphicsBoxItem(l, w, pallet);
					box->setPos(x, y);
					box->rotateAngle(rz);
					scene->addItem(box);

				}
			}

		}



	};

	auto dumpPallet = [this](QGraphicsScene* scene)
	{
		/**
		保存文件示例: json 格式
		{
			"tierName":"",
			"tierL":"1.2",
			"tierW":"1.0",
			"unitNum":10,
			"units":[
				{"bBucket":false,"l":0.55,"w":0.35,"x":0.42,"y":0.25,"rz":90},
				{"bBucket":true,"r":0.55,"x":0.42,"y":0.25}
			]
		}
		*/

		QGraphicsItem* parent = nullptr;
		for (const auto item : scene->selectedItems())
		{
			if (qgraphicsitem_cast<lxQGraphicsPalletItem*>(item))
			{
				parent = item;
				break;
			}
			if (item->parentItem())
			{
				parent = item->parentItem();
				break;
			}
		}
		if (parent)
		{
			QJsonDocument jDoc;
			QJsonObject jObj;
			QJsonArray jArr;

			jObj["tierName"] = "tier-1";
			jObj["tierL"] = parent->boundingRect().width()*mm2PixelRatio;
			jObj["tierW"] = parent->boundingRect().height()*mm2PixelRatio;
			for (const auto& item : parent->childItems())
			{
				QJsonObject jTmpObj;

				// 桶子
				if (qgraphicsitem_cast<lxQGraphicsBucketItem*>(item))
				{
					jTmpObj["bBucket"] = true;
					jTmpObj["r"] = item->boundingRect().width()/2.*mm2PixelRatio;

					auto itemInParent = parent->mapFromScene(item->scenePos());
					jTmpObj["x"] = itemInParent.x() *mm2PixelRatio;
					jTmpObj["y"] = itemInParent.y() *mm2PixelRatio;
				}
				else
				{
					jTmpObj["bBucket"] = false;
					jTmpObj["l"] = item->boundingRect().width()*mm2PixelRatio;
					jTmpObj["w"] = item->boundingRect().height()*mm2PixelRatio;

					auto itemInParent = parent->mapFromScene(item->scenePos());
					jTmpObj["x"] = itemInParent.x() *mm2PixelRatio;
					jTmpObj["y"] = itemInParent.y() *mm2PixelRatio;
					jTmpObj["rz"] = item->rotation();
				}

				jArr.append(jTmpObj);
			}
			jObj["unitNum"] = jArr.size();
			jObj["units"] = jArr;


			jDoc.setObject(jObj);
			const auto regExp = QRegularExpression(QString("\.json$"), QRegularExpression::CaseInsensitiveOption);

			QString fileName = QFileDialog::getSaveFileName(this);
			QString suffix = "";
			if (!fileName.contains(regExp))
				suffix = ".json";

			if (!fileName.isEmpty())
			{
				QFile file(fileName + suffix);
				if (!file.open(QIODevice::WriteOnly))
				{
					return;
				}
				file.write(jDoc.toJson());
			}
		}
	};


	/** 是否按下了ctrl*/
	if (event->key() == Qt::Key_Control)
	{
		mb_ctrl = true;
	}

	/** 快捷键操作*/
	switch (event->key())
	{
	case Qt::Key_C:
		if (mb_ctrl )
		{
			/** ctrl + c 拷贝选中的Item 到剪切板*/
			QApplication::clipboard()->setMimeData(new lxQShapeMimeData(scene()->selectedItems()));
		}
		break;
	case Qt::Key_V:
		if (mb_ctrl)
		{
			/** const_cast转换符是用来移除变量的const限定符*/
			QMimeData* md = const_cast<QMimeData*>(QApplication::clipboard()->mimeData());
			lxQShapeMimeData* data = dynamic_cast<lxQShapeMimeData*>(md);
			if (data)
			{
				scene()->clearSelection();
				/** ctrl + v 将剪切板的item再复制一份加入到scene中*/
				for (const auto&item : data->getItems())
				{
					auto _item = qgraphicsitem_cast<AbstractGraphicsItem*>(item);
					if (_item)
					{
						auto copy = _item->duplicate();
						copy->setSelected(true);
						copy->moveBy(10, 10);
						scene()->addItem(copy);
					}
				}
			}

			/** 更新剪切板中的内容*/
			QApplication::clipboard()->setMimeData(new lxQShapeMimeData(scene()->selectedItems()));
		}
		break;
	case Qt::Key_G:
		if (mb_ctrl)
		{
			/** 组合*/
			if (scene()->selectedItems().size() != 0)
			{
				auto _scene = dynamic_cast<lxQGraphicsScene*>(scene());
				auto g = _scene->createGroup(_scene->selectedItems(), true);
			}
		}
		break;
	case Qt::Key_U:
		if (mb_ctrl)
		{
			/** 打散组合*/
			if (scene()->selectedItems().size() != 0)
			{
				auto _scene = dynamic_cast<lxQGraphicsScene*>(scene());

				for (auto item : scene()->selectedItems())
				{
					if (auto group = qgraphicsitem_cast<lxQGraphicsItemGroup*>(item))
					{
						_scene->destroyGroup(group);
					}
				}
			}

		}
		break;
	case Qt::Key_Delete:
		deleteSelectItems(scene());
		break;
	case Qt::Key_A:
		if (mb_ctrl)
		{
			//attach 吸附到托盘  目前仅支持一个托盘
			attachToPallet(scene());
		}
		break;
	case Qt::Key_D:
		if (mb_ctrl)
		{
			// detach 从托盘脱离  目前仅支持一个托盘
			detachFromPallet(scene());
		}
		break;
	case Qt::Key_S:
		if (mb_ctrl)
		{
			// 保存托盘到文件
			dumpPallet(scene());
		}
		break;
	case Qt::Key_O:
		if (mb_ctrl)
		{
			// 从文件加载一个托盘
			loadPallet(scene());
		}
		break;
	default:
		break;
	}

	QGraphicsView::keyPressEvent(event);
}

void lxQGraphicsView::keyReleaseEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Control)
	{
		mb_ctrl = false;
	}

	QGraphicsView::keyReleaseEvent(event);
}

void lxQGraphicsView::wheelEvent(QWheelEvent *event)
{
	/**ctrl +:zoom in | ctrl - :zoom out*/
	if (mb_ctrl)
		scaleView(std::pow(2, event->delta() / 240.0));
	else
		translateViewY(event->delta()/10.);
}


void lxQGraphicsView::mousePressEvent(QMouseEvent *event)
{

	QGraphicsView::mousePressEvent(event);

	static bool bSelectMode = true;
	/** 按下中键切换模式*/ 
	if (event->buttons() == Qt::MidButton)
	{
		if (bSelectMode)
		{
			setDragMode(QGraphicsView::RubberBandDrag);
			bSelectMode = false;
		}
		else
		{
			setDragMode(QGraphicsView::ScrollHandDrag);
			bSelectMode = true;
		}
	}

	AbstractGraphicsItem* item = qgraphicsitem_cast<AbstractGraphicsItem*>(scene()->itemAt(mapToScene(event->pos()),QTransform()));

	lxQGraphicsRotateRing* ring = lxQGraphicsRotateRing::getInstance();
	lxQGraphicsTransCross* cross = lxQGraphicsTransCross::getInstance();

	bool ringEnable = mt_btnGroup->buttonChecked("btn-4");
	bool crossEnable = mt_btnGroup->buttonChecked("btn-5");


	if (item)
	{
		QPointF toolPos = item->scenePos();

		lxQGraphicsItemGroup* group = nullptr;
		if (group = qgraphicsitem_cast<lxQGraphicsItemGroup*>(item->parentItem()))
		{
			item = (AbstractGraphicsItem*)group;

			/**只有当group对象时 要计算tool pos*/
			auto rect = group->sceneBoundingRect();
			toolPos = rect.topLeft() + QPointF(rect.width(), rect.height()) / 2.;
		}
		else if(group = qgraphicsitem_cast<lxQGraphicsItemGroup*>(item))
		{
			/**只有当group对象时 要计算tool pos*/
			auto rect = group->sceneBoundingRect();
			toolPos = rect.topLeft() + QPointF(rect.width(), rect.height()) / 2.;
		}

		// 如果该item 有 parent item 就直接 return 了,即不能选中有parent 的item. 注意 不包含 group 
		if (item->parentItem() && group == nullptr)
		{
			return;
		}

		if (ringEnable)
		{
			ring->setPos(toolPos);
			if (item != ring)
				ring->setRotatedObj(item);
			scene()->addItem(ring);
		}

		if (crossEnable)
		{
			cross->setPos(toolPos);
			if (item != cross)
				cross->setTransObj(item);
			scene()->addItem(cross);
		}
	}
	else
	{

		scene()->removeItem(ring);
		scene()->removeItem(cross);
	}

	if(!ringEnable)
		scene()->removeItem(ring);
	if (!crossEnable)
		scene()->removeItem(cross);
	
	update();


}


void lxQGraphicsView::drawBackground(QPainter *painter, const QRectF &rect)
{
	QGraphicsView::drawBackground(painter, rect);

	QColor c(Qt::darkCyan);
	QPen p(c);
	p.setStyle(Qt::DashLine);
	p.setWidthF(0.2);
	painter->setPen(p);

	painter->save();
	painter->setRenderHints(QPainter::Antialiasing, false);

	//painter->fillRect(rect, Qt::white);
	for (int x = rect.left(); x < rect.right(); x += (int)(20)) {
		painter->drawLine(x, rect.top(), x, rect.bottom());

	}
	for (int y = rect.top(); y < rect.bottom(); y += (int)(20))
	{
		painter->drawLine(rect.left(), y, rect.right(), y);
	}
	p.setStyle(Qt::SolidLine);
	p.setColor(Qt::black);
	painter->drawLine(rect.right(), rect.top(), rect.right(), rect.bottom());
	painter->drawLine(rect.left(), rect.bottom(), rect.right(), rect.bottom());
	painter->restore();
}

void lxQGraphicsView::scaleView(qreal scaleFactor)
{
	qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();

	if (factor < 0.07 || factor > 100)
		return;

	scale(scaleFactor, scaleFactor);
}

void lxQGraphicsView::translateViewY(qreal dy)
{
	translate(0,dy);
}
