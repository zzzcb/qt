#include "webserver.h"
#include <QDebug>
#include <QtCore/QFile>


WebServer::WebServer(QObject *parent)
	: QObject(parent)
{
	m_pServer = new QTcpServer(this);
	m_pServer->listen(QHostAddress("127.0.0.1"), 80);

	m_pSocket = new QTcpSocket(this);
	connect(m_pServer, &QTcpServer::newConnection, this, &WebServer::slot_newConn);
}

WebServer::~WebServer()
{

}

void WebServer::slot_newConn()
{
	if (m_pServer->hasPendingConnections())
	{
		m_pSocket = m_pServer->nextPendingConnection();
	}
	
	connect(m_pSocket, &QTcpSocket::readyRead, this, &WebServer::slot_readyRead);
}

QByteArray sendRespose(QString path, QString type)
{
	QByteArray responseLine = "HTTP/1.1 200\r\n";
	QByteArray responseHeader="";
	QByteArray responseBlank = "\r\n";
	QByteArray responseBody="";

	QFile file(path);
	if (file.open(QFile::ReadOnly))
	{
		responseBody = file.readAll();
	}
	file.close();

	responseHeader = QString("Content-Length=%1\r\n").arg(responseBody.length()).toUtf8();
	if (type == "html")
		responseHeader += "Content-type=text/html\r\n";
	else if (type == "img")
		responseHeader += "Content-type=image/jpeg\r\n";

	return responseLine + responseHeader + responseBlank + responseBody;
}

QByteArray handleRequest(QString msg)
{
	QStringList urlPath = msg.split(" ");
	if (urlPath.size() >= 2)
	{
		QStringList args = urlPath.at(1).split("?");
		if (args.size() >= 2)
		{
			QStringList kvs = args.at(1).split("&");
			QString path = "";
			QString type = "";
			for (auto kv : kvs)
			{
				auto res = kv.split("=");
				if (res[0] == "path")
					path = res[1];
				else if (res[0] == "type")
					type = res[1];
			}

			return sendRespose(path, type);
		}
	}

	return "";
}

void WebServer::slot_readyRead()
{
	/** 开始从客户端 读消息*/
	QByteArray arr = m_pSocket->readAll();
	QString msg = QString::fromLocal8Bit(arr.trimmed());
		
	QByteArray res = handleRequest(msg);
	if (!res.isEmpty())
	{
		m_pSocket->write(res);
		m_pSocket->close();
	}
}
