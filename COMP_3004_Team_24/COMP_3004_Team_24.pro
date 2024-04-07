QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    handler.cpp \
    main.cpp \
    mainwindow.cpp \
    device_settings.cpp \
    eeg_interface.cpp \
    session_log.cpp \
    treatment_session.cpp \
    visual_feedback.cpp

HEADERS += \
    device_settings.h \
    handler.h \
    mainwindow.h \
    eeg_interface.h \
    session_log.h \
    treatment_session.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc
