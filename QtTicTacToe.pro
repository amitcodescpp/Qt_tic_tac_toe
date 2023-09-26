QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    computerplayer.cpp \
    gameviewinterface.cpp \
    main.cpp \
    tictactoecontroller.cpp \
    tictactoedatamodel.cpp

HEADERS += \
    commonUtil.h \
    computerplayer.h \
    gameviewinterface.h \
    tictactoecontroller.h \
    tictactoedatamodel.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    QtTicTacToe_en_US.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
