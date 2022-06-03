TEMPLATE = app
DEPENDPATH += .
INCLUDEPATH += .

include(../qtpropertybrowser/src/qtpropertybrowser.pri)
# Input
HEADERS += qtcanvas.h mainwindow.h
SOURCES += qtcanvas.cpp mainwindow.cpp main.cpp

