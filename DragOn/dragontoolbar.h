#ifndef DRAGONTOOLBAR_H
#define DRAGONTOOLBAR_H

#include <QMainWindow>


#include "dragonscene.h"
#include "CommandManager.h"

class DragOnToolBar
{
public:
    DragOnToolBar(QMainWindow * mainWindow, DragOnScene * scene, CommandManager *commandManager);

private:
    void createEditToolBar(QMainWindow *mainWindow,  DragOnScene * scene, CommandManager *commandManager);
    QAction * createUndoAction(QMainWindow *mainWindow, CommandManager *commandManager);
    QAction * createRedoAction(QMainWindow *mainWindow, CommandManager *commandManager);

    DragOnScene * scene;
    CommandManager commandManager;

};

#endif // DRAGONTOOLBAR_H
