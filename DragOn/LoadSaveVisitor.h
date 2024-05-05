#ifndef LOADSAVEVISITOR_H
#define LOADSAVEVISITOR_H

#include "itemvisitors.h"
#include "shapeitem.h"
#include "dragonscene.h"
#include<QTextStream>
#include <QGraphicsItem>

// Concrete Visitor: Save graphics items to a file
class SaveVisitor : public SceneItemVisitor {

public:
    SaveVisitor(QTextStream &stream) : out(stream) {}
    void visitSceneItem(QGraphicsItem *item) override;

private:
    void visitShapeItem(ShapeItem *item);

    QTextStream &out;
};


class SceneLoader {

public:
    SceneLoader(QTextStream &stream) : in(stream) {}
    void loadToScene(DragOnScene *scene);

private:
    QTextStream &in;
};


#endif // LOADSAVEVISITOR_H
