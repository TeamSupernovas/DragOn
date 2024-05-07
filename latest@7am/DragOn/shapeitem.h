#ifndef SHAPEITEM_H
#define SHAPEITEM_H

#include <QGraphicsPolygonItem>
#include <QColor>

#include "Command.h"
#include "itemvisitors.h"
#include "DragOnSceneItem.h"

enum class ShapeType {
    Rectangle,
    Circle,
    Line,
    Square,
    Triangle,
    Rhombus,
    Pentagon
};

class ShapeItem: public QGraphicsPolygonItem, public DragOnSceneItem
{
public:
    ShapeItem(ShapeType shapeType, QPolygonF polygon, const QColor &color = Qt::gray, QGraphicsItem *parent = nullptr);

    ShapeType getShapeType() const { return shapeType; }
    QPixmap image() const;
    int type() const override { return Type; }
    void accept(SceneItemVisitor *visitor);

    QColor getColor() const { return color; }
    void setColor(const QColor &newColor);

    void rotateAroundCenter(qreal angle); // Custom rotation function

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    ShapeType shapeType;
    QColor color;
    QColor originalColor; // Store the original color for undo
};

#endif // SHAPEITEM_H
