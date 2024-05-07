#ifndef SCENEMODESTATE_H
#define SCENEMODESTATE_H

#include <QGraphicsSceneDragDropEvent>
#include <DragOnScene.h>

class SceneModeState {
public:
    virtual void handleDropEvent(DragOnScene* context, QGraphicsSceneDragDropEvent* event) = 0;
};

#endif // SCENEMODESTATE_H
