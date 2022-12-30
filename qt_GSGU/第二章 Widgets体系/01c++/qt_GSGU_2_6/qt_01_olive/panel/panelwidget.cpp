#include "panelmanager.h"
#include "panelwidget.h"
#include <QPainter>

PanelWidget::PanelWidget(QWidget *parent)
	: QDockWidget(parent),m_bBorderVisible(false)
{
	setFocusPolicy(Qt::ClickFocus);

	PanelManager::instance()->registerPanel(this);
}

PanelWidget::~PanelWidget()
{
	PanelManager::instance()->unRegisterPanel(this);
}

void PanelWidget::setBorderVisible(bool visible)
{
	if (m_bBorderVisible == visible)
		return;

	m_bBorderVisible = visible;

	update();
}

void PanelWidget::paintEvent(QPaintEvent *event)
{
	QDockWidget::paintEvent(event);

	// Draw a highlight border
	if (m_bBorderVisible)
	{
		QPainter p(this);

		QRect highlightBorder = rect();
		highlightBorder.adjust(0, 0, -1, -1);

		p.setPen(palette().highlight().color());
		p.drawRect(highlightBorder);
	}
}
