QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AddCommand.cpp \
    Command.cpp \
    CommandManager.cpp \
    LoadSaveVisitor.cpp \
    MoveCommand.cpp \
    dragonscene.cpp \
    dragontoolbar.cpp \
    dragonview.cpp \
    filemanager.cpp \
    main.cpp \
    DragOnMainWindow.cpp \
    shapefactory.cpp \
    shapeitem.cpp \
    sidebar.cpp

HEADERS += \
    AddCommand.h \
    Command.h \
    CommandManager.h \
    DragOnMainWindow.h \
    LoadSaveVisitor.h \
    MoveCommand.h \
    dragonscene.h \
    dragontoolbar.h \
    dragonview.h \
    filemanager.h \
    itemvisitors.h \
    shapefactory.h \
    shapeitem.h \
    sidebar.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS +=

DISTFILES += \
    images/background1.png \
    images/background2.png \
    images/background3.png \
    images/background4.png \
    images/bold.png \
    images/bringtofront.png \
    images/delete.png \
    images/floodfill.png \
    images/italic.png \
    images/linecolor.png \
    images/linepointer.png \
    images/pointer.png \
    images/sendtoback.png \
    images/textpointer.png \
    images/underline.png

RESOURCES += \
    Resources.qrc
