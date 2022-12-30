#include "footagepanel/footagepanel.h"

FootagePanel::FootagePanel(QWidget *parent/*=nullptr*/)
	:PanelWidget(parent)
{
	setWindowTitle("Footage Viewer");
}

FootagePanel::~FootagePanel()
{
}
