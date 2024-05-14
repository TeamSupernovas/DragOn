#ifndef SAVEVISITOR_H
#define SAVEVISITOR_H

#include <QTextStream>
#include <QGraphicsItem>

#include "ItemVisitors.h"
#include "ShapeItem.h"
#include "TextItem.h"


class SaveVisitor : public SceneItemVisitor {

public:
    SaveVisitor(QTextStream &stream) : out(stream) {}

private:
    void visitShapeItem(ShapeItem *item) override;
    void visitTextItem(TextItem *item) override;

    QTextStream &out;
};

#endif // SAVEVISITOR_H
