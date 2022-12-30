#pragma once

#include "panelwidget.h"

class ToolPanel  : public PanelWidget
{
	Q_OBJECT

public:
	ToolPanel(QWidget *parent=nullptr);
	~ToolPanel();
};
