from PyQt5.QtCore import QDate, Qt


def printCurDate(format):
    print(QDate.currentDate().toString(format))


if __name__ == '__main__':
    printCurDate(Qt.ISODate)
    printCurDate(Qt.LocalDate)
    printCurDate(Qt.TextDate)
