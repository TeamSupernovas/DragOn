#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QString>
#include <QMainWindow>

#include "DragOnScene.h"
#include "ExportStrategy.h"

class FileManager {

public:
    FileManager();

    void saveSceneToFile(QMainWindow *mainWindow, DragOnScene * scene);
    void exportSceneToFile(QMainWindow *mainWindow, DragOnScene * scene, ExportStrategy * exportStrategy);
    void loadSceneFromFile(QMainWindow *mainWindow, DragOnScene * scene);

private:
    QString currentFilePath;

};

#endif // FILEMANAGER_H
