TEMPLATE = app
DEPENDPATH += .
INCLUDEPATH += .

include(../qtpropertybrowser/src/qtpropertybrowser.pri)
# Input
SOURCES += main.cpp

TRANSLATIONS += cn.ts

DISTFILES += \
    cn.ts

RESOURCES += \
    simple.qrc




