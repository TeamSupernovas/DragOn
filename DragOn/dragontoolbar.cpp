#include "dragontoolbar.h"
#include <QToolBar>
#include<QAction>


DragOnToolBar::DragOnToolBar(QMainWindow * mainWindow, DragOnScene * scene, CommandManager *commandManager) {
    createEditToolBar(mainWindow, scene, commandManager);
}


void DragOnToolBar::createEditToolBar(QMainWindow *mainWindow,  DragOnScene * scene, CommandManager *commandManager) {
    QToolBar * editToolBar = mainWindow->addToolBar(QMainWindow::tr("Edit"));
    editToolBar->addAction(createUndoAction(mainWindow, commandManager));
    editToolBar->addAction(createRedoAction(mainWindow, commandManager));



}

QAction * DragOnToolBar::createUndoAction(QMainWindow *mainWindow, CommandManager *commandManager) {
    qDebug() << "adding undo action";

    QAction * undoAction = new QAction(QIcon(":/images/delete.png"), QMainWindow::tr("&Undo"), mainWindow);
    undoAction->setShortcut(QKeySequence::Undo);
    undoAction->setStatusTip(QMainWindow::tr("Undo last action"));
    mainWindow->connect(undoAction, &QAction::triggered, [commandManager]() {
            qDebug() << "Undo received in lambda function";
            commandManager->undo();

        });

    return undoAction;
}


QAction * DragOnToolBar::createRedoAction(QMainWindow *mainWindow, CommandManager *commandManager) {
    qDebug() << "adding undo action";

    QAction * redoAction = new QAction(QIcon(":/images/sendtoback.png"), QMainWindow::tr("&Redo"), mainWindow);
    redoAction->setShortcut(QKeySequence::Redo);
    redoAction->setStatusTip(QMainWindow::tr("Redo last undo"));
    mainWindow->connect(redoAction, &QAction::triggered, [commandManager]() {
        qDebug() << "Undo received in lambda function";
        commandManager->redo();

    });

    return redoAction;
}
