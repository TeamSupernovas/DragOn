#ifndef DRAGONSCENEITEM_H
#define DRAGONSCENEITEM_H

#include <QPixmap>
#include <QGraphicsItem>
#include "itemvisitors.h"

class DragOnSceneItem {
public:
    virtual ~DragOnSceneItem(){}
    void  accept(SceneItemVisitor *visitor) {
        visitor->visitSceneItem(this);
    }
};

#endif // DRAGONSCENEITEM_H
