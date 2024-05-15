#include "SceneModeMoveItem.h"
#include <QGraphicsItem>
#include "CommandManager.h"
#include "MoveCommand.h"
#include "DragOnScene.h"

SceneModeMoveItem::SceneModeMoveItem(DragOnScene * scene) : SceneModeState(scene) {}

void SceneModeMoveItem::onMousePress(QGraphicsSceneMouseEvent *event) {
    // future enhancement
}

void SceneModeMoveItem::onDrop(QGraphicsSceneDragDropEvent *event) {
    if(scene->getSelectedItem()) {
        if (auto *graphicsItem = dynamic_cast<QGraphicsItem*>(scene->getSelectedItem())) {
            QPointF dropPos = event->scenePos();
            QPointF moveBy = dropPos - scene->getSceneDragStartPos();
            qDebug() << "moveBy: " << moveBy;
            if (moveBy.x() || moveBy.y()) {
                CommandManager::instance()->executeCommand(new MoveCommand(graphicsItem, moveBy));
            }
            scene->setMode(SceneMode::None);
            event->accept();
        }
    }

}

void SceneModeMoveItem::onDragMove(QGraphicsSceneDragDropEvent *event) {
    // future enhancement
}

