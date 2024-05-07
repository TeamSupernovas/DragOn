#include "dragontoolbar.h"
#include "filemanager.h"
#include <QToolBar>
#include <QAction>
#include <QFontComboBox>
#include <QToolButton>
#include <QComboBox>
#include <QColorDialog>
#include <QIntValidator>
#include "ExportToPNG.h"
#include "ExportToJPEG.h"
#include "colorcommand.h"
#include "rotationcommand.h"

// Function to create an undo action
QAction *createUndoAction(QMainWindow *mainWindow, CommandManager *commandManager) {
    QAction *undoAction = new QAction(QIcon(":/images/undo.png"), QMainWindow::tr("&Undo"), mainWindow);
    undoAction->setShortcut(QKeySequence::Undo);
    undoAction->setStatusTip(QMainWindow::tr("Undo last action"));
    mainWindow->connect(undoAction, &QAction::triggered, [commandManager]() {
        commandManager->undo();
    });

    return undoAction;
}

// Function to create a redo action
QAction *createRedoAction(QMainWindow *mainWindow, CommandManager *commandManager) {
    QAction *redoAction = new QAction(QIcon(":/images/redo.png"), QMainWindow::tr("&Redo"), mainWindow);
    redoAction->setShortcut(QKeySequence::Redo);
    redoAction->setStatusTip(QMainWindow::tr("Redo last undo"));
    mainWindow->connect(redoAction, &QAction::triggered, [commandManager]() {
        commandManager->redo();
    });

    return redoAction;
}

// Function to create a save action
QAction *createSaveAction(QMainWindow *mainWindow, DragOnScene *scene, FileManager *filemanager) {
    QAction *saveAction = new QAction(QIcon(":/images/save.png"), QMainWindow::tr("&Save"), mainWindow);
    saveAction->setShortcut(QKeySequence::Save);
    saveAction->setStatusTip(QMainWindow::tr("Save"));
    mainWindow->connect(saveAction, &QAction::triggered, [mainWindow, scene, filemanager]() {
        filemanager->saveSceneToFile(mainWindow, scene);
    });

    return saveAction;
}

// Function to create an export action
QAction *createExportAction(QMainWindow *mainWindow, DragOnScene *scene, ExportStrategy *exportStrategy, FileManager *filemanager) {
    QAction *exportAction = new QAction(
        exportStrategy->getIcon(),
        exportStrategy->getName(),
        mainWindow);

    exportAction->setStatusTip(exportStrategy->getName());
    mainWindow->connect(exportAction, &QAction::triggered, [mainWindow, scene, exportStrategy, filemanager]() {
        filemanager->exportSceneToFile(mainWindow, scene, exportStrategy);
    });

    return exportAction;
}

// Function to create an open file action
QAction *createOpenFileAction(QMainWindow *mainWindow, DragOnScene *scene, FileManager *filemanager) {
    QAction *openFileAction = new QAction(QIcon(":/images/open.jpg"), QMainWindow::tr("&Open File"), mainWindow);
    openFileAction->setShortcut(QKeySequence::Open);
    openFileAction->setStatusTip(QMainWindow::tr("Open File"));
    mainWindow->connect(openFileAction, &QAction::triggered, [mainWindow, scene, filemanager]() {
        filemanager->loadSceneFromFile(mainWindow, scene);
    });

    return openFileAction;
}

// Function to create a color action
QAction *createColorAction(QMainWindow *mainWindow, DragOnScene *scene) {
    QAction *colorAction = new QAction(QIcon(":/images/color.png"), "Color", mainWindow);
    colorAction->setStatusTip("Change Shape Color");
    mainWindow->connect(colorAction, &QAction::triggered, [scene]() {
        // Open a QColorDialog to pick a color
        QColor color = QColorDialog::getColor(Qt::black, nullptr, "Choose a Color");

        // Check if a color was selected
        if (color.isValid()) {
            // Apply the color to selected shapes
            QList<QGraphicsItem*> selectedItems = scene->selectedItems();
            for (QGraphicsItem *item : selectedItems) {
                ShapeItem *shapeItem = dynamic_cast<ShapeItem*>(item);
                if (shapeItem) {
                    QColor oldColor = shapeItem->getColor();
                    scene->getCommandManager()->executeCommand(new ColorCommand(shapeItem, oldColor, color));
                }
            }
        }
    });
    return colorAction;
}

QAction *createRotateAction(QMainWindow *mainWindow, DragOnScene *scene, qreal rotationAngle) {
    QAction *rotateAction = new QAction(QIcon(":/images/clock.png"), "Rotate", mainWindow);
    rotateAction->setStatusTip("Rotate Shape");
    mainWindow->connect(rotateAction, &QAction::triggered, [scene, rotationAngle]() {
        // Rotate selected shapes around their center
        QList<QGraphicsItem*> selectedItems = scene->selectedItems();
        for (QGraphicsItem *item : selectedItems) {
            ShapeItem *shapeItem = dynamic_cast<ShapeItem*>(item);
            if (shapeItem) {
                // Calculate the rotation point (center of the shape's bounding rect)
                QPointF rotationPoint = shapeItem->boundingRect().center();

                // Set the rotation point as the transform origin
                shapeItem->setTransformOriginPoint(rotationPoint);

                // Execute the rotate command
                scene->getCommandManager()->executeCommand(new RotateCommand(shapeItem, rotationAngle));
            }
        }
    });
    return rotateAction;
}






// Constructor for the DragOnToolBar class
DragOnToolBar::DragOnToolBar(QMainWindow *mainWindow, DragOnScene *scene, CommandManager *commandManager) {
    filemanager = new FileManager;
    exportStrategies.push_back(new ExportToPNG());
    exportStrategies.push_back(new ExportToJPEG());
    createFileToolBar(mainWindow, scene);
    createExportToolBar(mainWindow, scene);
    createEditToolBar(mainWindow, scene, commandManager);
    createFontToolBar(mainWindow, scene);
    createColorToolBar(mainWindow, scene);
    createRotateToolBar(mainWindow, scene);
}

// Function to create the file tool bar
void DragOnToolBar::createFileToolBar(QMainWindow *mainWindow, DragOnScene *scene) {
    QToolBar *fileToolBar = mainWindow->addToolBar(QMainWindow::tr("File"));
    fileToolBar->addAction(createSaveAction(mainWindow, scene, filemanager));
    fileToolBar->addAction(createOpenFileAction(mainWindow, scene, filemanager));
}

// Function to create the export tool bar
void DragOnToolBar::createExportToolBar(QMainWindow *mainWindow, DragOnScene *scene) {
    QToolBar *exportToolBar = mainWindow->addToolBar(QMainWindow::tr("Export"));

    for (auto& exportStrategy : exportStrategies) {
        exportToolBar->addAction(
            createExportAction(mainWindow, scene, exportStrategy, filemanager)
            );
    }
}

// Function to create the edit tool bar
void DragOnToolBar::createEditToolBar(QMainWindow *mainWindow, DragOnScene *scene, CommandManager *commandManager) {
    QToolBar *editToolBar = mainWindow->addToolBar(QMainWindow::tr("Edit"));
    editToolBar->addAction(createUndoAction(mainWindow, commandManager));
    editToolBar->addAction(createRedoAction(mainWindow, commandManager));
}

// Function to create the font tool bar
void DragOnToolBar::createFontToolBar(QMainWindow *mainWindow, DragOnScene *scene) {
    QFontComboBox *fontCombo = new QFontComboBox();
    scene->connect(fontCombo, &QFontComboBox::currentFontChanged,
                   [fontCombo, scene](){
                       QFont font = scene->currentFont();
                       font.setFamily(fontCombo->currentFont().family());
                       scene->setFont(font);
                   });

    QComboBox *fontSizeCombo = new QComboBox;
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

    QToolBar *fontToolBar = mainWindow->addToolBar(QMainWindow::tr("Font"));
    fontToolBar->addWidget(fontCombo);
    fontToolBar->addWidget(fontSizeCombo);
}

// Function to create the color tool bar
void DragOnToolBar::createColorToolBar(QMainWindow *mainWindow, DragOnScene *scene) {
    QToolButton *colorToolButton = new QToolButton;
    colorToolButton->setIcon(QIcon(":/images/color.png"));
    colorToolButton->setToolTip("Change Color");

    QAction *colorAction = createColorAction(mainWindow, scene);
    colorToolButton->setDefaultAction(colorAction);

    QToolBar *colorToolBar = mainWindow->addToolBar(QMainWindow::tr("Color"));
    colorToolBar->addWidget(colorToolButton);
}
QAction *createRotateAction(QMainWindow *mainWindow, DragOnScene *scene, qreal rotationAngle, const QString& iconPath) {
    QAction *rotateAction = new QAction(QIcon(iconPath), "Rotate", mainWindow);
    rotateAction->setStatusTip("Rotate Shape");
    mainWindow->connect(rotateAction, &QAction::triggered, [scene, rotationAngle]() {
        // Rotate selected shapes around their center
        QList<QGraphicsItem*> selectedItems = scene->selectedItems();
        for (QGraphicsItem *item : selectedItems) {
            ShapeItem *shapeItem = dynamic_cast<ShapeItem*>(item);
            if (shapeItem) {
                // Calculate the rotation point (center of the shape's bounding rect)
                QPointF rotationPoint = shapeItem->boundingRect().center();

                // Set the rotation point as the transform origin
                shapeItem->setTransformOriginPoint(rotationPoint);

                // Execute the rotate command
                scene->getCommandManager()->executeCommand(new RotateCommand(shapeItem, rotationAngle));
            }
        }
    });
    return rotateAction;
}

void DragOnToolBar::createRotateToolBar(QMainWindow *mainWindow, DragOnScene *scene) {
    qreal clockwiseRotationAngle = 45.0; // Angle for clockwise rotation
    qreal anticlockwiseRotationAngle = -45.0; // Angle for anticlockwise rotation

    // Create actions for clockwise and anticlockwise rotation
    QAction *clockwiseRotateAction = createRotateAction(mainWindow, scene, clockwiseRotationAngle, ":/images/clock.png");
    QAction *anticlockwiseRotateAction = createRotateAction(mainWindow, scene, anticlockwiseRotationAngle, ":/images/anti.png");

    // Create tool buttons for clockwise and anticlockwise rotation
    QToolButton *clockwiseRotateToolButton = new QToolButton;
    clockwiseRotateToolButton->setIcon(QIcon(":/images/clock.png"));
    clockwiseRotateToolButton->setToolTip("Rotate Clockwise");
    clockwiseRotateToolButton->setDefaultAction(clockwiseRotateAction);

    QToolButton *anticlockwiseRotateToolButton = new QToolButton;
    anticlockwiseRotateToolButton->setIcon(QIcon(":/images/anti.png"));
    anticlockwiseRotateToolButton->setToolTip("Rotate Anticlockwise");
    anticlockwiseRotateToolButton->setDefaultAction(anticlockwiseRotateAction);

    // Add tool buttons to the rotate toolbar
    QToolBar *rotateToolBar = mainWindow->addToolBar(QMainWindow::tr("Rotate"));
    rotateToolBar->addWidget(clockwiseRotateToolButton);
    rotateToolBar->addWidget(anticlockwiseRotateToolButton);
}
