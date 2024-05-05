#include "filemanager.h"
#include "LoadSaveVisitor.h"
#include <QString>
#include <QIODevice>
#include <QFileDialog>

FileManager::FileManager() {

}



void FileManager::saveSceneToFile(QMainWindow *mainWindow, DragOnScene * scene) {
    if (currentFilePath == nullptr) {
        currentFilePath = QFileDialog::getSaveFileName(mainWindow, QFileDialog::tr("Save File"), "", QFileDialog::tr("All Files (*.*)"));
    }
    if (!currentFilePath.isEmpty()) {
        QFile file(currentFilePath);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);

            SaveVisitor visitor(out);
            foreach (QGraphicsItem *item, scene->items()) {
                if (auto *shapeItem = dynamic_cast<ShapeItem*>(item)) {
                    shapeItem->accept(&visitor);
                }
                // Add more cases as needed for other item types
            }
            file.close();

        }
    }


}
void FileManager::loadSceneFromFile(QMainWindow *mainWindow, DragOnScene * scene){
    currentFilePath = QFileDialog::getOpenFileName(mainWindow, QFileDialog::tr("Open File"), "", QFileDialog::tr("All Files (*.*)"));
    if (!currentFilePath.isEmpty()) {
        QFile file(currentFilePath);
        if (file.open(QIODevice::ReadOnly)) {
            QTextStream in(&file);
            SceneLoader sceneloader(in);
            sceneloader.loadToScene(scene);
            file.close();

        }
    }

}