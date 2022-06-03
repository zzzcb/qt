TEMPLATE = app
DEPENDPATH += .
INCLUDEPATH += .

include(../qtpropertybrowser/src/qtpropertybrowser.pri)
# Input
SOURCES += main.cpp \
    mydoublepropertymanager.cpp \
    mydoublespinboxfactory.cpp

HEADERS += \
    mydoublepropertymanager.h \
    mydoublespinboxfactory.h

