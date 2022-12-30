#include "toolpanel/toolpanel.h"

ToolPanel::ToolPanel(QWidget *parent/*=nullptr*/)
	:PanelWidget(parent)
{
	setWindowTitle("Tools");
}

ToolPanel::~ToolPanel()
{
}
