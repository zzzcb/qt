#pragma once

#include "panelwidget.h"

class AudioPanel  : public PanelWidget
{
	Q_OBJECT

public:
	AudioPanel(QWidget *parent=nullptr);
	~AudioPanel();
};
