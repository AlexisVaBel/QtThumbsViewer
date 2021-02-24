CONFIG += app_bundle
CONFIG += c++11
CONFIG += qt

QT += core gui widgets
QT += concurrent

TEMPLATE = app

TARGET = thumb_viewer

SOURCES += \
        main.cpp \
        model/cfilethumbproxy.cpp \
        ui/cdirthumbsviewer.cpp

HEADERS += \
    model/cfilethumbproxy.h \
    ui/cdirthumbsviewer.h \
    view/cfileicondelegate.h \
    view/ciconlistview.h
