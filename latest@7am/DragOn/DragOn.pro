QT       += core gui svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AddShapeCommand.cpp \
    AddTextCommand.cpp \
    ChangeShapeColorCommand.cpp \
    ChangeTextColorCommand.cpp \
    ChangeTextFontCommand.cpp \
    Command.cpp \
    CommandManager.cpp \
    DragOnMainWindow.cpp \
    DragOnScene.cpp \
    DragOnToolbar.cpp \
    DragOnView.cpp \
    ExportToJPEG.cpp \
    ExportToPNG.cpp \
    FileManager.cpp \
    IconButton.cpp \
    LoadSaveVisitor.cpp \
    main.cpp \
    MoveCommand.cpp \
    PixmapGenerator.cpp \
    ResizeCommand.cpp \
    RotateCommand.cpp \
    ShapeFactory.cpp \
    ShapeItem.cpp \
    SideBar.cpp \
    TextItem.cpp

HEADERS += \
    AddShapeCommand.h \
    AddTextCommand.h \
    ChangeShapeColorCommand.h \
    ChangeTextColorCommand.h \
    ChangeTextFontCommand.h \
    Command.h \
    CommandManager.h \
    DragOnMainWindow.h \
    DragOnScene.h \
    DragOnSceneItem.h \
    DragOnToolbar.h \
    DragOnView.h \
    ExportStrategy.h \
    ExportToJPEG.h \
    ExportToPNG.h \
    FileManager.h \
    IconButton.h \
    ItemVisitors.h \
    LoadSaveVisitor.h \
    MoveCommand.h \
    PixmapGenerator.h \
    ResizeCommand.h \
    RotateCommand.h \
    SceneMode.h \
    SceneModeState.h \
    Serializable.h \
    ShapeFactory.h \
    ShapeItem.h \
    SideBar.h \
    TextItem.h

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
    images/underline.png \
    images/undo.png

RESOURCES += \
    Resources.qrc
