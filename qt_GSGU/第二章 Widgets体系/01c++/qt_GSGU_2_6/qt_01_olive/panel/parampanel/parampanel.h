#pragma once

#include "panelwidget.h"

class ParamPanel  : public PanelWidget
{
	Q_OBJECT

public:
	ParamPanel(QWidget *parent=nullptr);
	~ParamPanel();
};
