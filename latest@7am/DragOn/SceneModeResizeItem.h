#ifndef SCENEMODERESIZEITEM_H
#define SCENEMODERESIZEITEM_H

#include "SceneModeState.h"

class SceneModeResizeItem : public SceneModeState
{
public:
    SceneModeResizeItem(DragOnScene * scene);
    void onMousePress(QGraphicsSceneMouseEvent *event) override;
    void onDrop(QGraphicsSceneDragDropEvent *event) override;
};

#endif // SCENEMODERESIZEITEM_H
