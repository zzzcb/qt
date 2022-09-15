#include "demo.h"
#include <QtWidgets/QApplication>

#include "mydialogsplash.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	MyDialogSplash* splash = new MyDialogSplash; // 注意 别忘了释放内存，可以通过设置窗口属性 当关闭时自动释放内存
	if (splash->exec() == QDialog::Accepted)
	{
		Demo w;
		w.show();
		return a.exec();
	}

	return 0;
}
