#ifndef DRAGONTOOLBAR_H
#define DRAGONTOOLBAR_H

#include <QMainWindow>


#include "dragonscene.h"
#include "CommandManager.h"
#include "filemanager.h"
#include "exportstrategy.h"

#include <vector>

class DragOnToolBar
{
public:
    DragOnToolBar(QMainWindow * mainWindow, DragOnScene * scene, CommandManager *commandManager);

protected:
    void createFileToolBar(QMainWindow *mainWindow,  DragOnScene * scene);
    void createExportToolBar(QMainWindow *mainWindow,  DragOnScene * scene);
    void createEditToolBar(QMainWindow *mainWindow,  DragOnScene * scene, CommandManager *commandManager);
    void createFontToolBar(QMainWindow *mainWindow,  DragOnScene * scene);

private:
    DragOnScene * scene;
    FileManager * filemanager;

    std::vector<ExportStrategy *> exportStrategies;
};

#endif // DRAGONTOOLBAR_H
