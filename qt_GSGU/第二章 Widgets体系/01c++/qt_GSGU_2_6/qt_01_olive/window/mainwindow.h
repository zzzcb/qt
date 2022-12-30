#pragma once

#include <QMainWindow>

class PanelWidget;

class FootagePanel;
class ParamPanel;
class NodePanel;

class SequencePanel;
class ProjectPanel;
class ToolPanel;
class TimelinePanel;
class AudioPanel;

class MainWindow  : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent=nullptr);
	~MainWindow();

private:
	void setAppStyle();
	void createStandardPanels();
	void setDefaultLayout();

	// Standard panels
	FootagePanel* m_pFootagePanel;
	ParamPanel*   m_pParamPanel;
	NodePanel*    m_pNodePanel;

	SequencePanel* m_pSeqPanel;
	ProjectPanel*  m_pProjectPanel;
	ToolPanel*     m_pToolPanel;
	TimelinePanel* m_pTimelinePanel;
	AudioPanel*    m_pAudioPanel;
};
