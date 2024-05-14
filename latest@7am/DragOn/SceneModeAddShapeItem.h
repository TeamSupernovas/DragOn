#ifndef SCENEMODEADDSHAPEITEM_H
#define SCENEMODEADDSHAPEITEM_H

#include "SceneModeState.h"
class SceneModeAddShapeItem: public SceneModeState {

public:
    SceneModeAddShapeItem(DragOnScene * scene);
    void onMousePress(QGraphicsSceneMouseEvent *event) override;
    void onDrop(QGraphicsSceneDragDropEvent *event) override;
    void onDragMove(QGraphicsSceneDragDropEvent *event) override;
    void onDragEnter(QGraphicsSceneDragDropEvent *event) override;

};

#endif // SCENEMODEADDSHAPEITEM_H
