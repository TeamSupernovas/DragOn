#ifndef SCENEMODENONE_H
#define SCENEMODENONE_H

#include "SceneModeState.h"
class SceneModeNone : public SceneModeState
{
public:
    SceneModeNone(DragOnScene * scene);
    void onMousePress(QGraphicsSceneMouseEvent *event) override;
    void onDrop(QGraphicsSceneDragDropEvent *event) override;
};

#endif // SCENEMODENONE_H
