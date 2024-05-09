#ifndef DRAGONSCENEITEM_H
#define DRAGONSCENEITEM_H

#include <QPixmap>
#include <QGraphicsItem>

#include "ItemVisitors.h"

class DragOnSceneItem {
public:
    virtual ~DragOnSceneItem(){}
    virtual void  accept(SceneItemVisitor *visitor) = 0;
};

#endif // DRAGONSCENEITEM_H
