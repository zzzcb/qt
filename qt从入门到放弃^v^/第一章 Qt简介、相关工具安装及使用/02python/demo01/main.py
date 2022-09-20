from PyQt5.QtWidgets import QApplication,QMainWindow
import sys


if __name__ == '__main__':

    app = QApplication(sys.argv)

    mw = QMainWindow()
    mw.setWindowTitle("我不是Qt")
    mw.show()

    app.exec()

