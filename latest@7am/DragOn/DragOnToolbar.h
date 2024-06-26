#ifndef DRAGONTOOLBAR_H
#define DRAGONTOOLBAR_H

#include <QMainWindow>

#include "DragOnScene.h"
#include "FileManager.h"
#include "ExportStrategy.h"

#include <vector>

class DragOnToolBar {

public:
    DragOnToolBar(QMainWindow *mainWindow, DragOnScene *scene);

protected:
    void createFileToolBar(QMainWindow *mainWindow, DragOnScene *scene);
    void createExportToolBar(QMainWindow *mainWindow, DragOnScene *scene);
    void createEditToolBar(QMainWindow *mainWindow);
    void createFontToolBar(QMainWindow *mainWindow, DragOnScene *scene);
    void createColorToolBar(QMainWindow *mainWindow, DragOnScene *scene);
    void createRotateToolBar(QMainWindow *mainWindow, DragOnScene *scene); // Declaration for createRotateToolBar

private:
    //DragOnScene *scene;
    FileManager *filemanager;
    std::vector<ExportStrategy *> exportStrategies;
};

#endif // DRAGONTOOLBAR_H
