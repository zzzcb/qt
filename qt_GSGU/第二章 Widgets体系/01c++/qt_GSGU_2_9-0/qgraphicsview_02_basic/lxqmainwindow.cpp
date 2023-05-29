#pragma execution_character_set("utf-8")
#include "lxqmainwindow.h"

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QComboBox>
#include <QFileDialog>

#include <QFormLayout>
#include <QSpinBox>
#include <QLineEdit>

#include <QMouseEvent>

#include <QDebug>

lxQMainWindow::lxQMainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	initQSS();

	QWidget* centerWidget = new QWidget(this);
	setCentralWidget(centerWidget);

	QVBoxLayout* mainLayout = new QVBoxLayout(this);
	QHBoxLayout* toolBtnLayout = new QHBoxLayout(this);

	mainLayout->addLayout(toolBtnLayout);
	centralWidget()->setLayout(mainLayout);

	/**tool*/
	m_pItemTypeBtn = new QComboBox(this);
	m_pAddItemBtn = new QPushButton("新增Item");
	m_pClearSceneBtn = new QPushButton("清空Scene");
	toolBtnLayout->addWidget(m_pItemTypeBtn);
	toolBtnLayout->addWidget(m_pAddItemBtn);
	toolBtnLayout->addWidget(m_pClearSceneBtn);
	initItemTypeComboBox();

	/**view*/ 
	m_pGraphicsView = new QGraphicsView;
	mainLayout->addWidget(m_pGraphicsView);
	mainLayout->setContentsMargins(0,0,0,0);

	/**scene*/  
	m_pGraphicsScene = new QGraphicsScene(QRectF(-350, -350, 700, 700), this);
	m_pGraphicsView->setScene(m_pGraphicsScene);

	resize(800, 800);

	initConfigPanel();

	/**signal-slot*/
	connect(m_pAddItemBtn, &QPushButton::clicked, this, &lxQMainWindow::slot_toolBtn_handle);
	connect(m_pClearSceneBtn, &QPushButton::clicked, this, &lxQMainWindow::slot_toolBtn_handle);
	connect(m_pItemTypeBtn, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &lxQMainWindow::slot_toolBtn_handle);
}

lxQMainWindow::~lxQMainWindow()
{
}

void lxQMainWindow::initQSS()
{
	QString qss = R"(
QGraphicsView{
	background: #3f3f46;
	border: none;
}
)";
	setStyleSheet(qss);
}

void lxQMainWindow::initItemTypeComboBox()
{
	QStringList itemTypes = {
		"QGraphicsEllipseItem", "QGraphicsPathItem","QGraphicsPolygonItem","QGraphicsRectItem","QGraphicsSimpleTextItem",
		"-",
		"QGraphicsLineItem",
		"-",
		"QGraphicsPixmapItem"
	};
	m_pItemTypeBtn->addItems(itemTypes);
}

void lxQMainWindow::initConfigPanel()
{
	m_pConfigPanel = new QDialog(this);
	m_pFormLayout = new QFormLayout(m_pConfigPanel);

	auto okButton = new QPushButton(tr("OK"));
	auto cancelButton = new QPushButton(tr("Cancel"));
	connect(okButton, &QAbstractButton::clicked, m_pConfigPanel, &QDialog::accept);
	connect(cancelButton, &QAbstractButton::clicked, m_pConfigPanel, &QDialog::reject);

	auto buttonLayout = new QHBoxLayout;
	buttonLayout->addWidget(okButton);
	buttonLayout->addWidget(cancelButton);

	m_pFormLayout->addRow("", buttonLayout);
}

void lxQMainWindow::resetConfigPanel()
{
	while (m_pFormLayout->rowCount() > 1)
		m_pFormLayout->removeRow(0);
}

bool lxQMainWindow::eventFilter(QObject *watched, QEvent *event)
{
	if (watched == m_pCollectPointPanel)
	{
		if (event->type() == QMouseEvent::MouseButtonPress)
		{
			m_vPoints.push_back(((QMouseEvent*)event)->pos());
			return true;
		}
	}
	return QMainWindow::eventFilter(watched, event);
}

void lxQMainWindow::slot_toolBtn_handle(int data)
{
	if (sender() == m_pClearSceneBtn)
	{
		m_pGraphicsScene->clear();
	}
	else if (sender() == m_pAddItemBtn)
	{
		QString strType = m_pItemTypeBtn->currentText();

		if (strType == "-")
			return;

		QGraphicsItem* newItem;
		if (strType == "QGraphicsEllipseItem")
		{
			newItem = new QGraphicsEllipseItem;// rect 
			newItem->setFlag(QGraphicsItem::ItemIsMovable);
			resetConfigPanel();

			QSpinBox* xSpin = new QSpinBox; xSpin->setValue(10);
			QSpinBox* ySpin = new QSpinBox; ySpin->setValue(10);
			QSpinBox* wSpin = new QSpinBox; wSpin->setValue(50);
			QSpinBox* hSpin = new QSpinBox; hSpin->setValue(50);
			m_pFormLayout->insertRow(m_pFormLayout->rowCount() - 1, "x", xSpin);
			m_pFormLayout->insertRow(m_pFormLayout->rowCount() - 1, "y", ySpin);
			m_pFormLayout->insertRow(m_pFormLayout->rowCount() - 1, "w", wSpin);
			m_pFormLayout->insertRow(m_pFormLayout->rowCount() - 1, "h", hSpin);
			if (m_pConfigPanel->exec())
			{
				auto item = qgraphicsitem_cast<QGraphicsEllipseItem*>(newItem);
				if (item)
				{
					item->setRect(xSpin->value(), ySpin->value(), wSpin->value(), hSpin->value());
					m_pGraphicsScene->addItem(item);

					m_tPainterPath.addEllipse(xSpin->value(), ySpin->value(), wSpin->value(), hSpin->value());
				}
			}
		}
		else if (strType == "QGraphicsPathItem")
		{
			newItem = new QGraphicsPathItem;
			newItem->setFlag(QGraphicsItem::ItemIsMovable);
			resetConfigPanel();

			if (m_pConfigPanel->exec())
			{
				auto item = qgraphicsitem_cast<QGraphicsPathItem*>(newItem);
				if (item)
				{
					item->setPath(m_tPainterPath);
					m_pGraphicsScene->addItem(item);

					m_tPainterPath.clear();
				}
			}
		}
		else if (strType == "QGraphicsPolygonItem")
		{
			newItem = new QGraphicsPolygonItem; 
			newItem->setFlag(QGraphicsItem::ItemIsMovable);
			resetConfigPanel();

			m_vPoints.clear();

			m_pCollectPointPanel = new QWidget; m_pCollectPointPanel->setFixedSize(300, 300);
			m_pCollectPointPanel->installEventFilter(this);

			m_pFormLayout->insertRow(m_pFormLayout->rowCount() - 1, m_pCollectPointPanel);
			if (m_pConfigPanel->exec())
			{
				auto item = qgraphicsitem_cast<QGraphicsPolygonItem*>(newItem);
				if (item)
				{
					item->setPolygon(QPolygonF(m_vPoints));
					m_pGraphicsScene->addItem(item);
				}
			}

		}
		else if (strType == "QGraphicsRectItem")
		{
			newItem = new QGraphicsRectItem;	
			newItem->setFlag(QGraphicsItem::ItemIsMovable);
			resetConfigPanel();

			QSpinBox* xSpin = new QSpinBox; xSpin->setValue(10);
			QSpinBox* ySpin = new QSpinBox; ySpin->setValue(10);
			QSpinBox* wSpin = new QSpinBox; wSpin->setValue(50);
			QSpinBox* hSpin = new QSpinBox; hSpin->setValue(50);
			m_pFormLayout->insertRow(m_pFormLayout->rowCount() - 1, "x", xSpin);
			m_pFormLayout->insertRow(m_pFormLayout->rowCount() - 1, "y", ySpin);
			m_pFormLayout->insertRow(m_pFormLayout->rowCount() - 1, "w", wSpin);
			m_pFormLayout->insertRow(m_pFormLayout->rowCount() - 1, "h", hSpin);
			if (m_pConfigPanel->exec())
			{
				auto item = qgraphicsitem_cast<QGraphicsRectItem*>(newItem);
				if (item)
				{
					item->setRect(xSpin->value(), ySpin->value(), wSpin->value(), hSpin->value());
					m_pGraphicsScene->addItem(item);

					m_tPainterPath.addRect(xSpin->value(), ySpin->value(), wSpin->value(), hSpin->value());
				}
			}
		}
		else if (strType == "QGraphicsSimpleTextItem")
		{
			newItem = new QGraphicsSimpleTextItem; 
			newItem->setFlag(QGraphicsItem::ItemIsMovable);
			resetConfigPanel();

			QLineEdit* textEdit = new QLineEdit; textEdit->setText("Qt~");
			QSpinBox* fontSizeSpin = new QSpinBox; fontSizeSpin->setValue(15);
			QSpinBox* widthSpin = new QSpinBox; widthSpin->setValue(2);
			m_pFormLayout->insertRow(m_pFormLayout->rowCount() - 1, "simple text", textEdit);
			m_pFormLayout->insertRow(m_pFormLayout->rowCount() - 1, "font size", fontSizeSpin);
			m_pFormLayout->insertRow(m_pFormLayout->rowCount() - 1, "pen size", widthSpin);
			if (m_pConfigPanel->exec())
			{
				auto item = qgraphicsitem_cast<QGraphicsSimpleTextItem*>(newItem);
				if (item)
				{
					QFont font; font.setPixelSize(fontSizeSpin->value());
					QPen pen; pen.setWidth(widthSpin->value());
					item->setFont(font);
					item->setPen(pen);
					item->setText(textEdit->text());
					m_pGraphicsScene->addItem(item);

					m_tPainterPath.addText(0, 0, font, textEdit->text());
				}
			}
		}
		else if (strType == "QGraphicsLineItem")
		{
			newItem = new QGraphicsLineItem;	 
			newItem->setFlag(QGraphicsItem::ItemIsMovable);
			resetConfigPanel();

			QSpinBox* x1Spin = new QSpinBox; x1Spin->setValue(10);
			QSpinBox* y1Spin = new QSpinBox; y1Spin->setValue(10);
			QSpinBox* x2Spin = new QSpinBox; x2Spin->setValue(50);
			QSpinBox* y2Spin = new QSpinBox; y2Spin->setValue(50);
			QSpinBox* widthSpin = new QSpinBox; widthSpin->setValue(5);
			m_pFormLayout->insertRow(m_pFormLayout->rowCount() - 1, "x", x1Spin);
			m_pFormLayout->insertRow(m_pFormLayout->rowCount() - 1, "y", y1Spin);
			m_pFormLayout->insertRow(m_pFormLayout->rowCount() - 1, "w", x2Spin);
			m_pFormLayout->insertRow(m_pFormLayout->rowCount() - 1, "h", y2Spin);
			m_pFormLayout->insertRow(m_pFormLayout->rowCount() - 1, "pen width", widthSpin);
			if (m_pConfigPanel->exec())
			{
				auto item = qgraphicsitem_cast<QGraphicsLineItem*>(newItem);
				if (item)
				{
					QPen pen; pen.setWidth(widthSpin->value());
					item->setPen(pen);
					item->setLine(x1Spin->value(), y1Spin->value(), x2Spin->value(), y2Spin->value());
					m_pGraphicsScene->addItem(item);
				}
			}
		}
		else if (strType == "QGraphicsPixmapItem")
		{
			newItem = new QGraphicsPixmapItem;	 
			newItem->setFlag(QGraphicsItem::ItemIsMovable);
			resetConfigPanel();

			QString imgFile = QFileDialog::getOpenFileName(this, "请选取一个图片", "./", "Image(*.jpg *.png *bmp)");

			if (!imgFile.isEmpty())
			{
				auto item = qgraphicsitem_cast<QGraphicsPixmapItem*>(newItem);
				if (item)
				{
					item->setPixmap(QPixmap(imgFile).scaledToWidth(300));
					m_pGraphicsScene->addItem(item);
				}
			}
		}
	}
}

