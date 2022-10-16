#pragma once

#include <QObject>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>

class WebServer  : public QObject
{
	Q_OBJECT

public:
	WebServer(QObject *parent=nullptr);
	~WebServer();

private slots:
	void slot_newConn();
	void slot_readyRead();

private:
	QTcpServer * m_pServer;
	QTcpSocket * m_pSocket;


};
