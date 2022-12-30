#pragma once

#include "panelwidget.h"

class ProjectPanel  : public PanelWidget
{
	Q_OBJECT

public:
	ProjectPanel(QWidget *parent=nullptr);
	~ProjectPanel();
};
