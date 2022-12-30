#include "sequencepanel/sequencepanel.h"

SequencePanel::SequencePanel(QWidget *parent/*=nullptr*/)
	:PanelWidget(parent)
{
	setWindowTitle("Sequence Viewer");
}

SequencePanel::~SequencePanel()
{
}
