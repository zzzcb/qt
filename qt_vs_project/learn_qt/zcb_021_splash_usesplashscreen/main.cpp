#include "demo.h"
#include <QtWidgets/QApplication>
#include "QSplashScreen"
#include "QDesktopWidget"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	QPixmap pixmap(":/Demo/lxrobot.png");
	// 缩放图片和当前桌面的分辨率一致（比真实小些）
	QDesktopWidget* desktopWidget = a.desktop();
	QPixmap pixmapForSplash = pixmap.scaledToWidth(desktopWidget->screenGeometry().width() - 300);
	// 显示logo 
	QSplashScreen splash(pixmapForSplash);
	splash.setWindowFlag(Qt::WindowStaysOnTopHint);
	splash.show();

	// 响应用户 事件
	a.processEvents(); 

	Demo w;
    w.show();
	splash.finish(&w); // 等待w 显示完全后才会 splash 才会退出

    return a.exec();
}
