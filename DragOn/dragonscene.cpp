
#include "dragonscene.h"

#include<QGraphicsItem>
#include<QMimeData>
#include<QDrag>
#include <QGraphicsRectItem>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include "AddCommand.h"
#include "MoveCommand.h"

DragOnScene::DragOnScene(CommandManager * commandManager, QObject *parent): QGraphicsScene(parent), commandManager(commandManager)
{}

void DragOnScene::setMode(SceneMode mode) {
    sceneMode = mode;
}
void DragOnScene::setSelectedItem(ShapeItem * shapeItem) {
    selectedItem = shapeItem;
}

void DragOnScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    qDebug() << "scene mouse pressed";
    if (event->button() == Qt::LeftButton) {
        // Find the top-most item at the mouse position
        QGraphicsItem *item = itemAt(event->scenePos(), QTransform());
        if (item == selectedItem) {
            // should we do something??
            qDebug() << "mouse pressed on selected item";
        }
        else if (item && item->flags() & QGraphicsItem::ItemIsMovable) {
            if (auto *shapeItem = dynamic_cast<ShapeItem*>(item)) {
                event->accept();
                selectedItem = shapeItem;
                sceneMode = SceneMode::MoveItem;
                qDebug() << "scene mode is MoveItem now";


                // Create a MIME data object to hold the item's data
                QMimeData *mimeData = new QMimeData;
                mimeData->setText("Dragged Item");

                // Create a drag object and set the MIME data
                QDrag *drag = new QDrag(this);
                drag->setMimeData(mimeData);
                drag->setPixmap(shapeItem->image());

                // Start the drag operation
                drag->exec(Qt::MoveAction);
            }

        }
    }
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
            } else if (sceneMode == SceneMode::MoveItem) {
                commandManager->executeCommand(new MoveCommand(selectedItem, this, event->scenePos()));
                selectedItem = nullptr;
                sceneMode = SceneMode::None;
            }
        }
    }
    qDebug() << "Dropped Dropped:";
    //event->accept();
    //event->acceptProposedAction();
    QGraphicsScene::dropEvent(event);
}

void DragOnScene::dragMoveEvent(QGraphicsSceneDragDropEvent *event) {
    //qDebug() << "Drag Move Event";
}


void DragOnScene::dragEnterEvent(QGraphicsSceneDragDropEvent *event) {

    if (event->mimeData()->hasText()) {
        qDebug() << "dragEnterEvent has text: " << event->mimeData()->text();
        //event->accept();
    }
    qDebug() << "Drag entered entered";
    QGraphicsScene::dragEnterEvent(event);
}
