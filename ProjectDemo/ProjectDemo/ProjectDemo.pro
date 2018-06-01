#-------------------------------------------------
#
# Project created by liduoyou 2018-05-30T22:31:11
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProjectDemo
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    source/main.cpp \
    source/mainwidget.cpp \
    source/widgetcompanent/cursorposcalculator.cpp \
    source/widgetcompanent/frameless_helper.cpp \
    source/widgetcompanent/NScrollBar.cpp \
    source/widgetcompanent/widgetdata.cpp \
    source/uiwidgets/catalogselector.cpp \
    source/util/commonhelper.cpp \
    source/util/crc32.cpp \
    source/util/css.cpp \
    source/util/filelog.cpp \
    source/util/qsizepolicywidget.cpp \
    source/util/qwidgetutils.cpp \
    source/Blocks/baseblock.cpp \
    source/Blocks/connectblock.cpp \
    source/Blocks/percubeline.cpp \
    source/uiwidgets/blockpalette.cpp \
    source/Blocks/block_for.cpp \
    source/Blocks/block_if.cpp \
    source/Blocks/block_while.cpp \
    source/Blocks/blockbuilder.cpp \
    source/Blocks/blockicon.cpp \
    source/Blocks/blockproperty.cpp \
    source/Blocks/fordialog.cpp \
    source/Blocks/ifdialog.cpp \
    source/Blocks/setbreak_c.cpp \
    source/Blocks/setcontinue_c.cpp \
    source/Blocks/setreturn_c.cpp \
    source/Blocks/whiledialog.cpp \
    source/Blocks/basedialog.cpp \
    source/uiwidgets/projectview.cpp \
    source/Blocks/diaplayblock.cpp \
    source/Blocks/positionexamine.cpp \
    source/Blocks/move.cpp \
    source/Blocks/grab.cpp

HEADERS += \
    source/mainwidget.h \
    source/widgetcompanent/cursorposcalculator.h \
    source/widgetcompanent/frameless_helper.h \
    source/widgetcompanent/NScrollBar.h \
    source/widgetcompanent/widgetdata.h \
    source/uiwidgets/catalogselector.h \
    source/util/commonhelper.h \
    source/util/crc32.h \
    source/util/css.h \
    source/util/filelog.h \
    source/util/qsizepolicywidget.h \
    source/util/qwidgetutils.h \
    source/Blocks/baseblock.h \
    source/Blocks/connectblock.h \
    source/Blocks/percubeline.h \
    source/define.h \
    source/uiwidgets/blockpalette.h \
    source/Blocks/basedialog.h \
    source/Blocks/block_for.h \
    source/Blocks/block_if.h \
    source/Blocks/block_while.h \
    source/Blocks/blockbuilder.h \
    source/Blocks/blockicon.h \
    source/util/myfont.h \
    source/Blocks/blockproperty.h \
    source/Blocks/fordialog.h \
    source/Blocks/ifdialog.h \
    source/Blocks/setbreak_c.h \
    source/Blocks/setcontinue_c.h \
    source/Blocks/setreturn_c.h \
    source/Blocks/whiledialog.h \
    source/Blocks/basedialog.h \
    source/uiwidgets/projectview.h \
    source/Blocks/displayblock.h \
    source/Blocks/positionexamine.h \
    source/Blocks/move.h \
    source/Blocks/grab.h

FORMS += \
    source/mainwidget.ui

RESOURCES += \
    res.qrc
