#include "panelmanager.h"
#include "panelwidget.h"

#include <QMutex>
#include <QDebug>

QMutex mutex;

PanelManager* PanelManager::m_pInstance = nullptr;
PanelManager* PanelManager::instance()
{
	if (!m_pInstance)
	{
		QMutexLocker locker(&mutex);
		if (!m_pInstance)
			m_pInstance = new PanelManager;
	}

	return m_pInstance;
}

void PanelManager::registerPanel(PanelWidget* panel)
{
	m_listFocusHistory.append(panel);

	if (m_listFocusHistory.size() == 1) 
	{
		// This is the first panel, focus it
		panel->setBorderVisible(true);
	}
}

void PanelManager::unRegisterPanel(PanelWidget* panel)
{
	m_listFocusHistory.removeOne(panel);
}

PanelManager::PanelManager(QWidget *parent/*=nullptr*/)
{}

void PanelManager::slot_focusChanged(QWidget *old, QWidget *now)
{
	//qDebug() << "old and new " << old << " " << now;

	QObject* parent = now;
	PanelWidget* castPanel;

	// 找到顶层PanelWidget,以绘制高亮边界
	while (parent != nullptr)
	{
		castPanel = dynamic_cast<PanelWidget*>(parent);

		if (castPanel) 
		{
			if (m_listFocusHistory.first() != castPanel)
			{
				int panel_index = m_listFocusHistory.indexOf(castPanel);

				if (!m_listFocusHistory.isEmpty())
					m_listFocusHistory.first()->setBorderVisible(false);

				castPanel->setBorderVisible(true);

				if (panel_index == -1)
					m_listFocusHistory.prepend(castPanel);
				else
					m_listFocusHistory.move(panel_index, 0);
			}

			break;
		}

		parent = parent->parent();
	}
}
