#pragma once

#include <QObject>
class PanelWidget;

class PanelManager  : public QObject
{
	Q_OBJECT

public:
	static PanelManager* instance();

	void registerPanel(PanelWidget* panel);
	void unRegisterPanel(PanelWidget* panel);

public slots:
	void slot_focusChanged(QWidget *old, QWidget *now);

private:
	PanelManager(QWidget *parent = nullptr);
	static PanelManager* m_pInstance;

	QList<PanelWidget*> m_listFocusHistory;
};
