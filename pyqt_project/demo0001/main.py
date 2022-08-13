from PyQt5.QtWidgets import QApplication
from PyQt5.QtWidgets import QMainWindow
import sys

if __name__ == '__main__':
    app = QApplication(sys.argv)

    mw = QMainWindow()
    mw.show()

    app.exec()
