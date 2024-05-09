QT       += core gui svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AddShapeCommand.cpp \
    AddTextCommand.cpp \
    ChangeTextColorCommand.cpp \
    ChangeTextFontCommand.cpp \
    Command.cpp \
    CommandManager.cpp \
    ExportToJPEG.cpp \
    LoadSaveVisitor.cpp \
    MoveCommand.cpp \
    ResizeCommand.cpp \
    ChangeShapeColorCommand.cpp \
    TextItem.cpp \
    DragOnScene.cpp \
    DragOnToolbar.cpp \
    DragOnView.cpp \
    ExportToPNG.cpp \
    FileManager.cpp \
    IconButton.cpp \
    main.cpp \
    DragOnMainWindow.cpp \
    PixmapGenerator.cpp \
    RotationCommand.cpp \
    ShapeFactory.cpp \
    ShapeItem.cpp \
    Sidebar.cpp

HEADERS += \
    AddShapeCommand.h \
    AddTextCommand.h \
    ChangeTextColorCommand.h \
    ChangeTextFontCommand.h \
    ChangeShapeColorCommand.h \
    ExportToPNG.h \
    Command.h \
    CommandManager.h \
    DragOnMainWindow.h \
    DragOnSceneItem.h \
    ExportToJPEG.h \
    ExportStrategy.h \
    ItemVisitors.h \
    LoadSaveVisitor.h \
    MoveCommand.h \
    ResizeCommand.h \
    SceneMode.h \
    SceneModeState.h \
    Serializable.h \
    TextItem.h \
    DragOnScene.h \
    DragOnToolbar.h \
    DragOnView.h \
    ExportStrategy.h \
    ExportToPNG.h \
    FileManager.h \
    IconButton.h \
    PixmapGenerator.h \
    RotationCommand.h \
    ShapeFactory.h \
    ShapeItem.h \
    Sidebar.h

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
