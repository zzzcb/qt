#include <QtCore/QCoreApplication>
#include <QtNetwork/QTcpSocket>
#include <QtCore/QDebug>
#include <QThread>

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);


	QTcpSocket client;
	
	while (1)
	{
		client.connectToHost("www.baidu.com", 80);

		client.waitForConnected();  ///< 阻塞等待 

		/**发出请求*/
		QString requestLine = "GET / HTTP/1.1\r\n";
		QString requestHeader = "Host:www.baidu.com\r\n";
		QString requestBlank = "\r\n";
		QString requestBody = "\r\n";
		QString requestData = requestLine + requestHeader + requestBlank + requestBody;
		client.write(requestData.toUtf8());

		client.waitForReadyRead();  ///< 阻塞等待 
		qDebug() << client.readAll();
		
		QThread::sleep(1);
	}

    return a.exec();
}
