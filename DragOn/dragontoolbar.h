#ifndef DRAGONTOOLBAR_H
#define DRAGONTOOLBAR_H

#include <QMainWindow>


#include "dragonscene.h"
#include "CommandManager.h"
#include "filemanager.h"

class DragOnToolBar
{
public:
    DragOnToolBar(QMainWindow * mainWindow, DragOnScene * scene, CommandManager *commandManager);

private:
    void createFileToolBar(QMainWindow *mainWindow,  DragOnScene * scene);
    void createEditToolBar(QMainWindow *mainWindow,  DragOnScene * scene, CommandManager *commandManager);

    DragOnScene * scene;
    FileManager * filemanager;

};

#endif // DRAGONTOOLBAR_H
