# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Tools.
# ------------------------------------------------------

TEMPLATE = app
TARGET = lab1_qt
DESTDIR = ../x64/Debug
QT += core gui widgets
CONFIG += debug
DEFINES += _UNICODE _ENABLE_EXTENDED_ALIGNED_STORAGE WIN64 QT_DLL QT_WIDGETS_LIB
INCLUDEPATH += ./GeneratedFiles \
    . \
    ./GeneratedFiles/$(ConfigurationName)
PRECOMPILED_HEADER = stdafx.h
DEPENDPATH += .
MOC_DIR += ./GeneratedFiles/$(ConfigurationName)
OBJECTS_DIR += debug
UI_DIR += ./GeneratedFiles
RCC_DIR += ./GeneratedFiles
HEADERS += ./ProcessManager.h \
    ./stdafx.h \
    ./lab1_qt.h
SOURCES += ./lab1_qt.cpp \
    ./main.cpp \
    ./ProcessManager.cpp \
    ./stdafx.cpp
FORMS += ./lab1_qt.ui
RESOURCES += lab1_qt.qrc