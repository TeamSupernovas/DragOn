#include "SceneModeAddTextItem.h"
#include <TextItem.h>
#include "DragOnScene.h"
#include "CommandManager.h"
#include "AddTextCommand.h"

SceneModeAddTextItem::SceneModeAddTextItem(DragOnScene * scene) : SceneModeState(scene) {}

void SceneModeAddTextItem::onMousePress(QGraphicsSceneMouseEvent *event) {

}

void SceneModeAddTextItem::onDrop(QGraphicsSceneDragDropEvent *event)
{
    TextItem * textItem = TextItem::createTextItem(
        QString("lorem ipsum"),
        scene->currentFont(),
        scene->getTextItemColor()
        );
    textItem->setPos(event->scenePos());
    scene->setSelectedItem(textItem);
    qDebug() << "insert text item now";
    CommandManager::instance()->executeCommand(new AddTextCommand(textItem, scene));
    scene->setMode(SceneMode::None);
    event->accept();
}

void SceneModeAddTextItem::onDragMove(QGraphicsSceneDragDropEvent *event) {

}

void SceneModeAddTextItem::onDragEnter(QGraphicsSceneDragDropEvent *event) {

}
