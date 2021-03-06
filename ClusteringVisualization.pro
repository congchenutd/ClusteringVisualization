#-------------------------------------------------
#
# Project created by QtCreator 2017-06-28T16:22:43
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = ClusteringVisualization
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
        MainWindow.cpp \
	Main.cpp \
    GraphicsScene.cpp \
    ShapeItem.cpp \
    CellMap.cpp \
    GraphicsView.cpp \
    IPage.cpp \
    PageConstructions.cpp \
    PageWidget.cpp \
    PageClustering.cpp \
    CellMapModel.cpp \
    CellMapFileModel.cpp

HEADERS += \
        MainWindow.h \
    GraphicsScene.h \
    ShapeItem.h \
    CellMap.h \
    GraphicsView.h \
    IPage.h \
    PageConstructions.h \
    PageWidget.h \
    PageClustering.h \
    CellMapModel.h \
    CellMapFileModel.h

FORMS += \
        MainWindow.ui \
    PageConstructions.ui \
    PageWidget.ui

RESOURCES += \
    Resources.qrc

macx {
	ICON = Images/GuidedPlayIcon.icns
}
