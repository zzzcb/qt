#pragma once

#include "panelwidget.h"

class NodePanel  : public PanelWidget
{
	Q_OBJECT

public:
	NodePanel(QWidget *parent=nullptr);
	~NodePanel();
};
