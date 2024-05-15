#include "SceneModeNone.h"
#include "DragOnScene.h"
#include "ShapeItem.h"

SceneModeNone::SceneModeNone(DragOnScene * scene) : SceneModeState(scene) {}

void SceneModeNone::onMousePress(QGraphicsSceneMouseEvent *event) {
    qDebug() << "scene mouse pressed";
    scene->setDragCreated(false);
    if (event->button() == Qt::LeftButton) {
        if (scene->getSelectedItem()) {
            if (auto *selectedShapeItem = dynamic_cast<ShapeItem*>(scene->getSelectedItem())) {
                if (scene->canResize(selectedShapeItem->sceneBoundingRect(), event->scenePos())) {
                    scene->setDragCreated(true);
                    // start Resize
                    event->accept();
                    scene->setSelectedItem(scene->getSelectedItem());
                    scene->setMode(SceneMode::ResizeItem);
                    qDebug() << "scene mode is ResizeItem now";

                    QDrag *drag = scene->createDrag("Resize");

                    // Start the drag operation
                    drag->exec(Qt::MoveAction);
                }
            }

        }
        if (!scene->getDragCreated()){
            // Find the top-most item at the mouse position
            QGraphicsItem *graphicsItem = scene->itemAt(event->scenePos(), QTransform());
            if (graphicsItem == nullptr) {
                scene->unSelectIfSelectedItem();
            }
            else if (auto *sceneItem = dynamic_cast<DragOnSceneItem*>(graphicsItem)) {
                if (graphicsItem && graphicsItem->flags() & QGraphicsItem::ItemIsMovable) {
                    event->accept();
                    scene->setSelectedItem(sceneItem);
                    scene->setMode(SceneMode::MoveItem);
                    qDebug() << "scene mode is MoveItem now";

                    QDrag *drag = scene->createDrag("Move");
                    if (auto *shapeItem = dynamic_cast<ShapeItem*>(graphicsItem)) {
                        drag->setPixmap(shapeItem->image());
                    }
                    drag->setHotSpot((event->scenePos() - graphicsItem->scenePos()).toPoint());
                    scene->setDragCreated(true);
                    // Start the drag operation
                    drag->exec(Qt::MoveAction);
                }
            }
        }
    }

}

void SceneModeNone::onDrop(QGraphicsSceneDragDropEvent *event) {

}

void SceneModeNone::onDragMove(QGraphicsSceneDragDropEvent *event) {

}
