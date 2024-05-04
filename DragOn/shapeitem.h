#ifndef SHAPEITEM_H
#define SHAPEITEM_H

#include <QGraphicsPixmapItem>
#include <QGraphicsPolygonItem>
#include <QList>



QT_BEGIN_NAMESPACE
class QPixmap;
class QGraphicsSceneContextMenuEvent;
class QMenu;
class QPolygonF;
QT_END_NAMESPACE


enum class ShapeType {
    Rectangle/*,
    Square,
    Circle,
    Rhombus,
    Polygon*/
};

class ShapeItem: public QGraphicsPolygonItem
{
public:
    enum { Type = UserType + 15 };

    ShapeItem(ShapeType shapeType, QPolygonF polygon, QGraphicsItem *parent = nullptr);

    ShapeType getShapeType() const { return shapeType; }
    QPixmap image() const;
    int type() const override { return Type; }

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

private:
    ShapeType shapeType;
};

#endif // SHAPEITEM_H
