QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    date.cpp \
    item.cpp \
    main.cpp \
    mainwindow.cpp \
    member.cpp \
    receipt.cpp \
    set.cpp

HEADERS += \
    date.h \
    item.h \
    mainwindow.h \
    member.h \
    receipt.h \
    set.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Sale_day1.txt \
    Sale_day10.txt \
    Sale_day11.txt \
    Sale_day12.txt \
    Sale_day2.txt \
    Sale_day3.txt \
    Sale_day4.txt \
    Sale_day5.txt \
    Sale_day6.txt \
    Sale_day7.txt \
    Sale_day8.txt \
    Sale_day9.txt \
    memberFile.txt \
    memberFileOriginal.txt
