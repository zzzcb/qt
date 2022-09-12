from PyQt5.QtWidgets import QApplication, QMainWindow
from PyQt5.QtGui import QIcon
import sys
import pkg_resources

if __name__ == '__main__':
    app = QApplication(sys.argv)

    iconPath = pkg_resources.resource_filename(
        "orangecanvas", "icons/orange-canvas.svg"
    )  # 第一个参数为包名  第二个参数为相对于包的路径
    app.setWindowIcon(QIcon(iconPath))
    mw = QMainWindow()
    mw.show()

    exit(app.exec())
