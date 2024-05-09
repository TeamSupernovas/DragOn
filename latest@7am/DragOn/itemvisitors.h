#ifndef ITEMVISITORS_H
#define ITEMVISITORS_H

class ShapeItem;
class TextItem;

// iterface to visit all shapes
class SceneItemVisitor
{
public:
    virtual void visitShapeItem(ShapeItem *item) = 0;
    virtual void visitTextItem(TextItem *item) = 0;
    virtual ~SceneItemVisitor() {}
};

#endif // ITEMVISITORS_H
