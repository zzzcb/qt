#include "rasterwindow.h"

#include <QDebug>
#include <QPainter>
#include <QResizeEvent>

RasterWindow::RasterWindow(QWindow *parent)
	: QWindow(parent),
	mp_backingStore(new QBackingStore(this))
{
	setGeometry(100, 100, 300, 200);
}

RasterWindow::~RasterWindow()
{


}

void RasterWindow::exposeEvent(QExposeEvent *event)
{
	qDebug() << "-------expose event ";
	qDebug() << "-------is expose  "<<isExposed();

	if (isExposed())
	{
		// 该窗口可见,如果不可见，就没必要更新了
		renderNow();
	}
}

void RasterWindow::resizeEvent(QResizeEvent *event)
{
	// 一定要给 QBackingStore resize 不然会崩溃
	mp_backingStore->resize(event->size());
}

bool RasterWindow::event(QEvent* event)
{
	// 稍后 渲染
	if (event->type() == QEvent::UpdateRequest)
	{
		renderNow();
		return true;
	}

	return QWindow::event(event);
}




void RasterWindow::renderNow()
{
	if (!isExposed())
		return;

	QRect rect(0, 0, width(), height());
	mp_backingStore->beginPaint(rect);  // 要在 qpainter绘制前调用

	QPaintDevice *device = mp_backingStore->paintDevice();
	QPainter painter(device);
	painter.fillRect(0, 0, width(), height(), QGradient::NightFade);
	render(&painter);

	mp_backingStore->endPaint();
	mp_backingStore->flush(rect);
}

void RasterWindow::renderLater()
{
	requestUpdate();  	// 稍后 渲染
}

void RasterWindow::render(QPainter *painter)
{
	painter->drawText(QRectF(0, 0, width(), height()), Qt::AlignCenter, QStringLiteral("QWindow"));
}