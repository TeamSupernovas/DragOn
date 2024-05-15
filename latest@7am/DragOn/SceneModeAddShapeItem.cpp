#include "SceneModeAddShapeItem.h"
#include "ShapeItem.h"
#include <QMimeData>
#include "DragOnScene.h"
#include "CommandManager.h"
#include "AddShapeCommand.h"

SceneModeAddShapeItem::SceneModeAddShapeItem(DragOnScene * scene) : SceneModeState(scene) {}

void SceneModeAddShapeItem::onMousePress(QGraphicsSceneMouseEvent *event) {
    // future enhancement
}

void SceneModeAddShapeItem::onDrop(QGraphicsSceneDragDropEvent *event) {
    if(scene->getSelectedItem()) {
        if (auto *shapeItem = dynamic_cast<ShapeItem*>(scene->getSelectedItem())) {
            shapeItem->setPos(event->scenePos());
            CommandManager::instance()->executeCommand(new AddShapeCommand(shapeItem, scene));
            scene->setMode(SceneMode::None);
            event->accept();
        }
    }
}

void SceneModeAddShapeItem::onDragMove(QGraphicsSceneDragDropEvent *event) {
    // future enhancement
}
