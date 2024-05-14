#ifndef SCENEMODEADDTEXTITEM_H
#define SCENEMODEADDTEXTITEM_H

#include "SceneModeState.h"

class SceneModeAddTextItem : public SceneModeState {

public:
    SceneModeAddTextItem(DragOnScene * scene);
    void onMousePress(QGraphicsSceneMouseEvent *event) override;
    void onDrop(QGraphicsSceneDragDropEvent *event) override;
    void onDragMove(QGraphicsSceneDragDropEvent *event) override;
    void onDragEnter(QGraphicsSceneDragDropEvent *event) override;
};

#endif // SCENEMODEADDTEXTITEM_H
