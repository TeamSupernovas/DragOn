#include "dragonscene.h"

DragOnScene::DragOnScene( QObject *parent): QGraphicsScene(parent)
{}

void DragOnScene::setMode(SceneMode mode) {
    sceneMode = mode;
}
void DragOnScene::setSelectedItem(ShapeItem * shapeItem) {
    selectedItem = shapeItem;
}
