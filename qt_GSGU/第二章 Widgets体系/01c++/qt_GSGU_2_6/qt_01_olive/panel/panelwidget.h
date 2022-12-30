#pragma once

#include <QDockWidget>

class PanelWidget  : public QDockWidget
{
	Q_OBJECT

public:
	PanelWidget(QWidget *parent=nullptr);
	~PanelWidget();

	void setBorderVisible(bool visible);

protected:
	void paintEvent(QPaintEvent *event) override;

private:
	bool m_bBorderVisible;
};



