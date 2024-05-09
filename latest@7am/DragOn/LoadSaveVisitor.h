#ifndef LOADSAVEVISITOR_H
#define LOADSAVEVISITOR_H

#include <QTextStream>
#include <QGraphicsItem>

#include "ItemVisitors.h"
#include "ShapeItem.h"
#include "DragOnScene.h"
#include "TextItem.h"

// Concrete Visitor: Save graphics items to a file
class SaveVisitor : public SceneItemVisitor {

public:
    SaveVisitor(QTextStream &stream) : out(stream) {}

private:
    void visitShapeItem(ShapeItem *item) override;
    void visitTextItem(TextItem *item) override;

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
