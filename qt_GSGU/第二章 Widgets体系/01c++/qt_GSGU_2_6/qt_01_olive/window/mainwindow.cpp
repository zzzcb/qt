#include "mainwindow.h"


// standard panel
#include "panelwidget.h"
#include "panelmanager.h"
#include "footagepanel/footagepanel.h"
#include "parampanel/parampanel.h"
#include "nodepanel/nodepanel.h"
#include "sequencepanel/sequencepanel.h"
#include "projectpanel/projectpanel.h"
#include "toolpanel/toolpanel.h"
#include "timelinepanel/timelinepanel.h"
#include "audiopanel/audiopanel.h"

#include <QApplication>  // for qApp
#include <QStyleFactory> 

#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	// Create empty central widget - we don't actually want a central widget (so we set its maximum
	// size to 0,0) but some of Qt's docking/undocking fails without it
	QWidget* centralWidget = new QWidget(this);
	centralWidget->setMaximumSize(QSize(0, 0));
	setCentralWidget(centralWidget);

	// 多个Dock形成tab容器时,tab栏位置设置
	setTabPosition(Qt::AllDockWidgetAreas, QTabWidget::North);

	// Allow panels to be tabbed within each other
	setDockNestingEnabled(true);

	// Create standard panels
	createStandardPanels();

	// Set default layout 
	setDefaultLayout();

	// Set style 
	setAppStyle();

	connect(qApp, &QApplication::focusChanged, PanelManager::instance(), &PanelManager::slot_focusChanged);
}

MainWindow::~MainWindow()
{}

void MainWindow::setAppStyle()
{
	// style
	qApp->setStyle(QStyleFactory::create("Fusion"));

	// palette 
	QPalette palette;
	palette.setColor(QPalette::All, QPalette::AlternateBase, QColor("#D0D0D0"));
	palette.setColor(QPalette::All, QPalette::Base, QColor("#F0F0F0"));
	palette.setColor(QPalette::All, QPalette::BrightText, QColor("#FF0000"));
	palette.setColor(QPalette::All, QPalette::Button, QColor("#D0D0D0"));
	palette.setColor(QPalette::All, QPalette::ButtonText, QColor("#000000"));
	palette.setColor(QPalette::All, QPalette::Highlight, QColor("#2A82DA"));
	palette.setColor(QPalette::All, QPalette::HighlightedText, QColor("#FFFFFF"));
	palette.setColor(QPalette::All, QPalette::Link, QColor("#2A82DA"));
	palette.setColor(QPalette::All, QPalette::Text, QColor("#000000"));
	palette.setColor(QPalette::All, QPalette::ToolTipBase, QColor("#FFFFFF"));
	palette.setColor(QPalette::All, QPalette::ToolTipText, QColor("#000000"));
	palette.setColor(QPalette::All, QPalette::Window, QColor("#D0D0D0"));
	palette.setColor(QPalette::All, QPalette::WindowText, QColor("#000000"));
	qApp->setPalette(palette);

	// qss
}

void MainWindow::createStandardPanels()
{
	m_pFootagePanel = new FootagePanel(this);
	m_pParamPanel = new ParamPanel(this);
	m_pNodePanel = new NodePanel(this);

	m_pSeqPanel = new SequencePanel(this);
	m_pProjectPanel = new ProjectPanel(this);
	m_pToolPanel = new ToolPanel(this);
	m_pTimelinePanel = new TimelinePanel(this);
	m_pAudioPanel = new AudioPanel(this);
}

void MainWindow::setDefaultLayout()
{
	resize(1000, 600);

	// top 
	m_pFootagePanel->show();
	addDockWidget(Qt::TopDockWidgetArea, m_pFootagePanel);
	m_pParamPanel->show();
	tabifyDockWidget(m_pFootagePanel, m_pParamPanel);
	m_pNodePanel->show();
	tabifyDockWidget(m_pParamPanel, m_pNodePanel);

	m_pSeqPanel->show();
	addDockWidget(Qt::TopDockWidgetArea, m_pSeqPanel);

	// bottom
	m_pProjectPanel->show();
	addDockWidget(Qt::BottomDockWidgetArea, m_pProjectPanel);

	m_pToolPanel->show();
	addDockWidget(Qt::BottomDockWidgetArea, m_pToolPanel);

	m_pTimelinePanel->show();
	addDockWidget(Qt::BottomDockWidgetArea, m_pTimelinePanel);

	m_pAudioPanel->show();
	addDockWidget(Qt::BottomDockWidgetArea, m_pAudioPanel);

	resizeDocks({ m_pParamPanel, m_pSeqPanel }, { width() / 2, width() / 2 }, Qt::Horizontal);
	resizeDocks({ m_pProjectPanel, m_pToolPanel, m_pTimelinePanel, m_pAudioPanel },{ width() / 4,  width() / 8, width(),  width() / 8 },Qt::Horizontal);

	resizeDocks({ m_pNodePanel, m_pProjectPanel },{ height() / 2, height() / 2 },Qt::Vertical);
}

