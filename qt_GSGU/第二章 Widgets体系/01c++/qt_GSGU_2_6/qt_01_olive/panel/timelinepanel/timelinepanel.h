#pragma once

#include "panelwidget.h"

class TimelinePanel  : public PanelWidget
{
	Q_OBJECT

public:
	TimelinePanel(QWidget *parent=nullptr);
	~TimelinePanel();
};
