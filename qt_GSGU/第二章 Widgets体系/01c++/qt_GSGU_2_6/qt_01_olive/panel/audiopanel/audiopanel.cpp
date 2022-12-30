#include "audiopanel/audiopanel.h"

AudioPanel::AudioPanel(QWidget *parent/*=nullptr*/)
	:PanelWidget(parent)
{
	setWindowTitle("Audio Manager");
}

AudioPanel::~AudioPanel()
{
}
