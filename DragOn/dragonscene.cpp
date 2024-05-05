
#include "dragonscene.h"

#include<QGraphicsItem>
#include<QMimeData>
#include<QDrag>
#include <QGraphicsRectItem>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include "AddCommand.h"

DragOnScene::DragOnScene(CommandManager * commandManager, QObject *parent): QGraphicsScene(parent), commandManager(commandManager)
{}

void DragOnScene::setMode(SceneMode mode) {
    sceneMode = mode;
}
void DragOnScene::setSelectedItem(ShapeItem * shapeItem) {
    selectedItem = shapeItem;
}

void DragOnScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    /*if (event->button() == Qt::LeftButton) {
        // Find the top-most item at the mouse position
        QGraphicsItem *item = itemAt(event->scenePos(), QTransform());
        if (item && item->isMovable()) {
            // Create a MIME data object to hold the item's data
            QMimeData *mimeData = new QMimeData;
            mimeData->setText("Dragged Item");

            // Create a drag object and set the MIME data
            QDrag *drag = new QDrag(this);
            drag->setMimeData(mimeData);

            // Start the drag operation
            drag->exec(Qt::MoveAction);
        }
    }*/
    QGraphicsScene::mousePressEvent(event);
}

void DragOnScene::dropEvent(QGraphicsSceneDragDropEvent *event) {
    qDebug() << "Dropped Dropped:";
    const QMimeData *mimeData = event->mimeData();
    if (mimeData->hasText()) {
        QString text = mimeData->text();
        qDebug() << "Dropped text:" << text;
        if (selectedItem) {
            if (sceneMode == SceneMode::AddItem) {
                selectedItem->setPos(event->scenePos());
                commandManager->executeCommand(new AddCommand(selectedItem, this));
                selectedItem = nullptr;
                sceneMode = SceneMode::None;
            }
        }
    }
    qDebug() << "Dropped Dropped:";
    //event->accept();
    event->acceptProposedAction();
    QGraphicsScene::dropEvent(event);
}

void DragOnScene::dragMoveEvent(QGraphicsSceneDragDropEvent *event) {
    //QGraphicsScene::dragMoveEvent(event);
}

void DragOnScene::dragEnterEvent(QGraphicsSceneDragDropEvent *event) {
    if (event->mimeData()->hasText()) {
        qDebug() << "dragEnterEvent has text";
        //event->accept();
    }
    qDebug() << "Drag entered entered";
    QGraphicsScene::dragEnterEvent(event);

}
