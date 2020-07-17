#-------------------------------------------------
#
# Project created by QtCreator 2018-05-20T03:42:12
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SqlFrontend
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#---------------------------------------------------------------------------------------------------
# version
#---------------------------------------------------------------------------------------------------

DEFINES += MAJOR_VERSION=1
DEFINES += MINOR_VERSION=0

#---------------------------------------------------------------------------------------------------
# Destination directory
#---------------------------------------------------------------------------------------------------
DESTDIR = ../bin

#---------------------------------------------------------------------------------------------------
# Source files
#---------------------------------------------------------------------------------------------------

SOURCES += \
    src/main.cpp \
    src/MainWindow.cpp \
    src/HomeForm.cpp \
    src/AboutDialog.cpp \
    src/utils.cpp \
    src/DbTablesForm.cpp \
    src/DbTableStructureForm.cpp \
    src/DbInfoTableForm.cpp \
    src/ScriptForm.cpp \
    src/SqlHighlighter.cpp \
    src/SettingsDialog.cpp

HEADERS += \
    src/MainWindow.h \
    src/HomeForm.h \
    src/AboutDialog.h \
    src/DbTablesForm.h \
    src/DbTableStructureForm.h \
    src/ISetCurrentWidget.h \
    src/DbInfoTableForm.h \
    src/ScriptForm.h \
    src/SqlHighlighter.h \
    src/utils.h \
    src/SettingsDialog.h

FORMS += \
    src/MainWindow.ui \
    src/HomeForm.ui \
    src/AboutDialog.ui \
    src/DbTablesForm.ui \
    src/DbTableStructureForm.ui \
    src/DbInfoTableForm.ui \
    src/ScriptForm.ui \
    src/SettingsDialog.ui

#---------------------------------------------------------------------------------------------------
# Resource files
#---------------------------------------------------------------------------------------------------

RESOURCES += res/resource.qrc

win32:RC_FILE = res/resource_win32.rc

#---------------------------------------------------------------------------------------------------
# Translation files
#---------------------------------------------------------------------------------------------------
TRANSLATIONS = \
    translation/mysqlfrontend_es.ts \
    translation/mysqlfrontend_en.ts
