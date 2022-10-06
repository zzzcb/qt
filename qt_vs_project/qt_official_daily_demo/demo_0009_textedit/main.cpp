/**
1,QCommandLineParser命令行解析
2,窗口刚一开始运行时放在窗口中间
3,菜单栏,工具栏设置
*/
#include "demo.h"
#include <QApplication>

#include <QCommandLineParser>
#include <QCommandLineOption>

#include <QDesktopWidget>

#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
	QCoreApplication::setOrganizationName("ZCB");
	QCoreApplication::setApplicationName("Rich Text");
	QCoreApplication::setApplicationVersion("0.0.1");
	
	/**arg parser*/
	QCommandLineParser parser; ///< 命令行解析器
	parser.setApplicationDescription("Usage: prog.exe [option]");
	parser.addHelpOption();
	parser.addVersionOption();
	parser.addPositionalArgument("file", "The file to open.");
	parser.process(app);
	//qDebug() << parser.positionalArguments(); /// 所有的位置参数
	//QString file= parser.positionalArguments().value(0,":/example.html");
	//qDebug() << "-------------> "<<file;   

	Demo w;

	/**center mainwindow*/
	const QRect availableGeometry = QApplication::desktop()->availableGeometry(&w);
	w.resize(availableGeometry.width() / 2, (availableGeometry.height() * 2) / 3);
	w.move((availableGeometry.width() - w.width()) / 2,
		(availableGeometry.height() - w.height()) / 2);

	if (!w.load(parser.positionalArguments().value(0, ":/example.html")))
		w.newFile();

    w.show();
    return app.exec();
}
