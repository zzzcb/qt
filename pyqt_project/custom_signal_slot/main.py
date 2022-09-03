from PyQt5.QtCore import QObject, pyqtSignal as Signal


class Demo(QObject):
    clicked = Signal(str)


def slot(s: str):
    print("receive:", s)


if __name__ == '__main__':
    d = Demo()
    d.clicked.connect(slot)  # 连接信号和槽

    d.clicked.emit("tom")  # 发射信号
    d.clicked.emit("jack")  # 发射信号
