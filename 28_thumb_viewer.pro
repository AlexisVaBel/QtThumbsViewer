CONFIG += app_bundle
CONFIG += c++11
CONFIG += qt

QT += core gui widgets
QT += concurrent

TEMPLATE = app

TARGET = thumb_viewer

SOURCES += \
        file_io/cthumbsloader.cpp \
        main.cpp \
        model/cfilethumbproxy.cpp \
        ui/cdirthumbsviewer.cpp

HEADERS += \
    file_io/cthumbsloader.h \
    model/cfilethumbproxy.h \
    ui/cdirthumbsviewer.h \
    view/cfileicondelegate.h \
    view/ciconlistview.h
