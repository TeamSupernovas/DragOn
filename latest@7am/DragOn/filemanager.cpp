#include "FileManager.h"
#include "LoadSaveVisitor.h"
#include "PixmapGenerator.h"
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
            scene->accept(&visitor);
            file.close();

        }
    }

}

void FileManager::exportSceneToFile(QMainWindow *mainWindow, DragOnScene * scene, ExportStrategy * exportStrategy) {

    QString exportFilename = QFileDialog::getSaveFileName(
        mainWindow,
        exportStrategy->getName(),
        QString("image.") + exportStrategy->getExtension(),
        QString("All Files (*.") + exportStrategy->getExtension() + QString(")")
        );
    QPixmap pixmap = PixmapGenerator::createPixmapFromScene(scene);
    exportStrategy->exportScene(pixmap, exportFilename);
}

void FileManager::loadSceneFromFile(QMainWindow *mainWindow, DragOnScene * scene){
    currentFilePath = QFileDialog::getOpenFileName(mainWindow, QFileDialog::tr("Open File"), "", QFileDialog::tr("All Files (*)"));
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
