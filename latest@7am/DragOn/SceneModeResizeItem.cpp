#include "SceneModeResizeItem.h"
#include "DragOnScene.h"
#include "ShapeItem.h"
#include "CommandManager.h"
#include "ResizeCommand.h"

SceneModeResizeItem::SceneModeResizeItem(DragOnScene * scene) : SceneModeState(scene) {}

void SceneModeResizeItem::onMousePress(QGraphicsSceneMouseEvent *event) {

}

void SceneModeResizeItem::onDrop(QGraphicsSceneDragDropEvent *event) {
    if(scene->getSelectedItem()){
        if (auto *shapeItem = dynamic_cast<ShapeItem*>(scene->getSelectedItem())) {
            QPointF newBottomRight = event->scenePos() - shapeItem->pos();
            QPointF changeBoundingRectSizeBy = newBottomRight - shapeItem->polygon().boundingRect().bottomRight();
            CommandManager::instance()->executeCommand(new ResizeCommand(shapeItem, changeBoundingRectSizeBy));
            scene->setMode(SceneMode::None);
            event->accept();
        }
    }
}

void SceneModeResizeItem::onDragMove(QGraphicsSceneDragDropEvent *event) {

}

void SceneModeResizeItem::onDragEnter(QGraphicsSceneDragDropEvent *event) {

}
