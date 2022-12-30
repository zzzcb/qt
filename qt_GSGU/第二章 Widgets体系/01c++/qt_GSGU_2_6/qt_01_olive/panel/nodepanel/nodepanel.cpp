#include "nodepanel/nodepanel.h"

#include <QVBoxLayout>

NodePanel::NodePanel(QWidget *parent/*=nullptr*/)
	:PanelWidget(parent)
{
	setWindowTitle("Node Editor");
}

NodePanel::~NodePanel()
{
}
