#include "dragontoolbar.h"
#include "filemanager.h"
#include <QToolBar>
#include<QAction>
#include <QFontComboBox>
#include <QToolButton>
#include <QComboBox>
#include <QColorDialog>
#include <QIntValidator>
#include "ExportToPNG.h"
#include "ExportToJPEG.h"


QAction * createUndoAction(QMainWindow *mainWindow, CommandManager *commandManager) {
    QAction * undoAction = new QAction(QIcon(":/images/delete.png"), QMainWindow::tr("&Undo"), mainWindow);
    undoAction->setShortcut(QKeySequence::Undo);
    undoAction->setStatusTip(QMainWindow::tr("Undo last action"));
    mainWindow->connect(undoAction, &QAction::triggered, [commandManager]() {
        commandManager->undo();

    });

    return undoAction;
}

QAction * createRedoAction(QMainWindow *mainWindow, CommandManager *commandManager) {
    QAction * redoAction = new QAction(QIcon(":/images/sendtoback.png"), QMainWindow::tr("&Redo"), mainWindow);
    redoAction->setShortcut(QKeySequence::Redo);
    redoAction->setStatusTip(QMainWindow::tr("Redo last undo"));
    mainWindow->connect(redoAction, &QAction::triggered, [commandManager]() {
        commandManager->redo();

    });

    return redoAction;
}

QAction * createSaveAction(QMainWindow *mainWindow, DragOnScene * scene, FileManager * filemanager) {
    QAction * saveAction = new QAction(QIcon(":/images/sendtoback.png"), QMainWindow::tr("&Save"), mainWindow);
    saveAction->setShortcut(QKeySequence::Save);
    saveAction->setStatusTip(QMainWindow::tr("Save"));
    mainWindow->connect(saveAction, &QAction::triggered, [mainWindow, scene, filemanager]() {
        filemanager->saveSceneToFile(mainWindow, scene);

    });

    return saveAction;
}

QAction * createExportAction(QMainWindow *mainWindow, DragOnScene * scene, ExportStrategy * exportStrategy, FileManager * filemanager) {
    QAction * exportAction = new QAction(
        exportStrategy->getIcon(),
        exportStrategy->getName(),
        mainWindow);

    exportAction->setStatusTip(exportStrategy->getName());
    mainWindow->connect(exportAction, &QAction::triggered, [mainWindow, scene, exportStrategy, filemanager]() {
        filemanager->exportSceneToFile(mainWindow, scene, exportStrategy);

    });

    return exportAction;
}


QAction * createOpenFileAction(QMainWindow *mainWindow, DragOnScene * scene, FileManager * filemanager) {
    QAction * openFileAction = new QAction(QIcon(":/images/sendtoback.png"), QMainWindow::tr("&Open File"), mainWindow);
    openFileAction->setShortcut(QKeySequence::Open);
    openFileAction->setStatusTip(QMainWindow::tr("Open File"));
    mainWindow->connect(openFileAction, &QAction::triggered, [mainWindow, scene, filemanager]() {
        filemanager->loadSceneFromFile(mainWindow, scene);

    });

    return openFileAction;
}



DragOnToolBar::DragOnToolBar(QMainWindow * mainWindow, DragOnScene * scene, CommandManager *commandManager) {
    filemanager = new FileManager;
    exportStrategies.push_back(new ExportToPNG());
    exportStrategies.push_back(new ExportToJPEG());
    createFileToolBar(mainWindow, scene);
    createExportToolBar(mainWindow, scene);
    createEditToolBar(mainWindow, scene, commandManager);
    createFontToolBar(mainWindow, scene);
}

void DragOnToolBar::createFileToolBar(QMainWindow *mainWindow,  DragOnScene * scene) {
    QToolBar * fileToolBar = mainWindow->addToolBar(QMainWindow::tr("File"));
    fileToolBar->addAction(createSaveAction(mainWindow, scene, filemanager));
    fileToolBar->addAction(createOpenFileAction(mainWindow, scene, filemanager));
}

void DragOnToolBar::createExportToolBar(QMainWindow *mainWindow,  DragOnScene * scene) {
    QToolBar * exportToolBar = mainWindow->addToolBar(QMainWindow::tr("Export"));

    for (auto& exportStrategy : exportStrategies) {
        exportToolBar->addAction(
            createExportAction(mainWindow, scene, exportStrategy, filemanager)
        );
    }
}


void DragOnToolBar::createEditToolBar(QMainWindow *mainWindow,  DragOnScene * scene, CommandManager *commandManager) {
    QToolBar * editToolBar = mainWindow->addToolBar(QMainWindow::tr("Edit"));
    editToolBar->addAction(createUndoAction(mainWindow, commandManager));
    editToolBar->addAction(createRedoAction(mainWindow, commandManager));
}

void DragOnToolBar::createFontToolBar(QMainWindow *mainWindow,  DragOnScene * scene) {
    QFontComboBox * fontCombo = new QFontComboBox();
    scene->connect(fontCombo, &QFontComboBox::currentFontChanged,
                        [fontCombo, scene](){
        QFont font = scene->currentFont();
        font.setFamily(fontCombo->currentFont().family());
        scene->setFont(font);
    });

    QComboBox * fontSizeCombo = new QComboBox;
    fontSizeCombo->setEditable(true);
    for (int i = 8; i < 30; i = i + 2)
        fontSizeCombo->addItem(QString().setNum(i));
    QIntValidator *validator = new QIntValidator(2, 64);
    fontSizeCombo->setValidator(validator);
    scene->connect(fontSizeCombo, &QComboBox::currentTextChanged, [fontSizeCombo, scene] () {
        QFont font = scene->currentFont();
        font.setPointSize(fontSizeCombo->currentText().toInt());
        scene->setFont(font);
    });


    QToolButton * textColorToolButton = new QToolButton;
    textColorToolButton->setIcon(QIcon(":/images/textpointer.png"));

    scene->connect(textColorToolButton, &QToolButton::clicked, [scene]() {
        // Open a QColorDialog to pick a color
        QColor color = QColorDialog::getColor(Qt::black, nullptr, "Choose a Color");

        // Check if a color was selected
        if (color.isValid()) {
            // Print the selected color
            qDebug() << "Selected color:" << color.name();
            scene->setTextColor(color);
        }
    });

    QToolBar * fontToolBar = mainWindow->addToolBar(QMainWindow::tr("Font"));
    fontToolBar->addWidget(fontCombo);
    fontToolBar->addWidget(fontSizeCombo);
    fontToolBar->addWidget(textColorToolButton);
}



