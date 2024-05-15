#include "SceneModeState.h"
#include <QMimeData>
#include <QGraphicsScene>
#include "DragOnScene.h"

SceneModeState::SceneModeState(DragOnScene* scene) : scene(scene){}

void SceneModeState::onDragEnter(QGraphicsSceneDragDropEvent *event) {
    if (event->mimeData()->hasText()) {
        qDebug() << "dragEnterEvent has text: " << event->mimeData()->text();
    }
    scene->setSceneDragStartPos(event->scenePos());
    qDebug() << "Drag entered at:" << scene->getSceneDragStartPos() ;
}
