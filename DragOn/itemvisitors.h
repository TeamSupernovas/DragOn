#ifndef ITEMVISITORS_H
#define ITEMVISITORS_H

#include <QGraphicsItem>

// iterface to visit all shapes
class SceneItemVisitor
{
public:
    virtual void visitSceneItem(QGraphicsItem *item) = 0;
    virtual ~SceneItemVisitor() {}
};



#endif // ITEMVISITORS_H
