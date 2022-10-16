/**
	1,QCommandLineParser命令行解析
	2,窗口刚一开始运行时放在窗口中间
*/
#include "demo.h"

#include <QApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QDesktopWidget>
#include <QSettings>

#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

	/**application config*/
	QCoreApplication::setOrganizationDomain("baidu.com2");
	QCoreApplication::setApplicationName("Rich Text2");
	QCoreApplication::setApplicationVersion("0.0.1");
	QSettings::setDefaultFormat(QSettings::IniFormat);   /**一定要设置*/
	
	/**arg parser*/
	QCommandLineParser parser; ///< 命令行解析器
	parser.setApplicationDescription("Usage: prog.exe [option]");
	parser.addHelpOption();
	parser.addVersionOption();
	parser.addPositionalArgument("file", "The file to open.");
	parser.process(app);

	Demo w;

	/**center mainwindow*/
	const QRect availableGeometry = QApplication::desktop()->availableGeometry(&w);
	w.resize(availableGeometry.width() / 2, (availableGeometry.height() * 2) / 3);
	w.move((availableGeometry.width() - w.width()) / 2,
		(availableGeometry.height() - w.height()) / 2);


	QString fileName = parser.positionalArguments().value(0);
	if (!fileName.isEmpty())
	{
		/**保存配置*/
		QSettings settings;
		settings.beginGroup("mainwindow");
		settings.setValue("recent-file-path", fileName);
	}
	else
	{
		/**读取配置文件*/
		QSettings settings;
		settings.beginGroup("mainwindow");
		fileName = settings.value("recent-file-path").toString();
	}


	if (!w.load(fileName))
	{
		w.newFile();
	}

    w.show();
    return app.exec();
}
