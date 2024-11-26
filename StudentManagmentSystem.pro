QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    admin.cpp \
    adminui.cpp \
    course.cpp \
    event.cpp \
    main.cpp \
    loginui.cpp \
    student.cpp \
    studentui.cpp \
    user.cpp

HEADERS += \
    admin.h \
    adminui.h \
    course.h \
    event.h \
    loginui.h \
    student.h \
    studentui.h \
    user.h

FORMS += \
    adminui.ui \
    loginui.ui \
    studentui.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
