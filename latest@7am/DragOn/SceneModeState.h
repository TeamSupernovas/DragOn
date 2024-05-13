#ifndef SCENEMODESTATE_H
#define SCENEMODESTATE_H

#include <QGraphicsSceneDragDropEvent>
#include <QGraphicsSceneMouseEvent>

class DragOnScene;

class SceneModeState
{
public:
    SceneModeState(DragOnScene* scene);
    virtual void onMousePress(QGraphicsSceneMouseEvent *event) = 0;
    virtual void onDrop(QGraphicsSceneDragDropEvent *event) = 0;

protected:
    DragOnScene* scene;
};

#endif // SCENEMODESTATE_H
