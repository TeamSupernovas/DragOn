#ifndef SHAPEITEM_H
#define SHAPEITEM_H

#include <QGraphicsPixmapItem>
#include <QGraphicsPolygonItem>
#include <QList>

#include "itemvisitors.h"



QT_BEGIN_NAMESPACE
class QPixmap;
class QGraphicsSceneContextMenuEvent;
class QMenu;
class QPolygonF;
QT_END_NAMESPACE


enum class ShapeType {
    Rectangle,
    Circle,
    Line
};

class ShapeItem: public QGraphicsPolygonItem
{
public:
    enum { Type = UserType + 15 };

    ShapeItem(ShapeType shapeType, QPolygonF polygon, QGraphicsItem *parent = nullptr);

    ShapeType getShapeType() const { return shapeType; }
    QPixmap image() const;
    int type() const override { return Type; }
    void accept(SceneItemVisitor *visitor);

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

private:
    ShapeType shapeType;
};

#endif // SHAPEITEM_H
