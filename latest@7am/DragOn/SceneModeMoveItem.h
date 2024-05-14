#ifndef SCENEMODEMOVEITEM_H
#define SCENEMODEMOVEITEM_H

#include "SceneModeState.h"

class SceneModeMoveItem : public SceneModeState {

public:
    SceneModeMoveItem(DragOnScene * scene);
    void onMousePress(QGraphicsSceneMouseEvent *event) override;
    void onDrop(QGraphicsSceneDragDropEvent *event) override;
    void onDragMove(QGraphicsSceneDragDropEvent *event) override;
    void onDragEnter(QGraphicsSceneDragDropEvent *event) override;
};

#endif // SCENEMODEMOVEITEM_H
