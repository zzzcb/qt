#include "parampanel/parampanel.h"

ParamPanel::ParamPanel(QWidget *parent/*=nullptr*/)
	:PanelWidget(parent)
{
	setWindowTitle("Parameter Editor");
}

ParamPanel::~ParamPanel()
{
}
