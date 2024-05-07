#ifndef ITEMVISITORS_H
#define ITEMVISITORS_H


class DragOnSceneItem;

// iterface to visit all shapes
class SceneItemVisitor
{
public:
    virtual void visitSceneItem(DragOnSceneItem *item) = 0;
    virtual ~SceneItemVisitor() {}
};



#endif // ITEMVISITORS_H
