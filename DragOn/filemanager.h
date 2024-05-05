#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "dragonscene.h"
#include <QString>
#include <QMainWindow>

class FileManager
{
public:
    FileManager();

    void saveSceneToFile(QMainWindow *mainWindow, DragOnScene * scene);
    void loadSceneFromFile(QMainWindow *mainWindow, DragOnScene * scene);

private:
    QString currentFilePath;

};

#endif // FILEMANAGER_H
