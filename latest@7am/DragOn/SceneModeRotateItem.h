#ifndef SCENEMODEROTATEITEM_H
#define SCENEMODEROTATEITEM_H

#include "SceneModeState.h"

class SceneModeRotateItem : public SceneModeState {

public:
    SceneModeRotateItem(DragOnScene * scene);
    void onMousePress(QGraphicsSceneMouseEvent *event) override;
    void onDrop(QGraphicsSceneDragDropEvent *event) override;
    void onDragMove(QGraphicsSceneDragDropEvent *event) override;

};

#endif // SCENEMODEROTATEITEM_H
