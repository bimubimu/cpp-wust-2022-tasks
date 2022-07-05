#-------------------------------------------------
#
# Project created by QtCreator 2022-06-05T14:42:27
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HotelManagement
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


SOURCES += \
        main.cpp \
        kmainwindow.cpp \
        toolbar.cpp \
    database/kdatabase.cpp \
    hotelService/kpriceinfo.cpp \
    hotelService/kroominfo.cpp \
    hotelWidget/kpriceinfowidget.cpp \
    hotelWidget/kregisterwidget.cpp \
    hotelWidget/kroominfowidget.cpp \
    loginDialog/logindialog.cpp \
    loginService/loginservice.cpp \
    hotelService/kregister.cpp \
    hotelWidget/kemployeewidget.cpp \
    hotelService/kemployee.cpp \
    hotelWidget/ktableview.cpp


HEADERS += \
        kmainwindow.h \
        toolbar.h \
    database/kdatabase.h \
    hotelService/kpriceinfo.h \
    hotelService/kroominfo.h \
    hotelWidget/kpriceinfowidget.h \
    hotelWidget/kregisterwidget.h \
    hotelWidget/kroominfowidget.h \
    loginDialog/logindialog.h \
    loginService/loginservice.h \
    hotelService/kregister.h \
    hotelWidget/kemployeewidget.h \
    hotelService/kemployee.h \
    hotelWidget/ktableview.h


FORMS += \
        kmainwindow.ui \
    hotelWidget/kpriceinfowidget.ui \
    hotelWidget/kregisterwidget.ui \
    hotelWidget/kroominfowidget.ui \
    loginDialog/logindialog.ui \
    hotelWidget/kemployeewidget.ui


RESOURCES += \
    res.qrc
