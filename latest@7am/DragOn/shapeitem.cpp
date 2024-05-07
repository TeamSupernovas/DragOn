#include "shapeitem.h"
#include <QPainter>
#include <QStyle>
#include<QStyleOptionGraphicsItem>

ShapeItem::ShapeItem(ShapeType shapeType, QPolygonF polygon, const QColor &color, QGraphicsItem *parent)
    : QGraphicsPolygonItem(polygon, parent), shapeType(shapeType), color(color), originalColor(color) {

    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    //setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}

QPixmap ShapeItem::image() const
{
    // Calculate the bounding rectangle of the polygon
    QRectF boundingRect = polygon().boundingRect().normalized();

    // Create a pixmap with the size of the bounding rectangle
    QPixmap pixmap(boundingRect.size().toSize() * 2);

    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.translate(-boundingRect.topLeft());
    painter.setPen(QPen(Qt::black, 2));
    painter.setBrush(color); // Set the color
    painter.drawPolygon(polygon()); // Fill the polygon with color

    return pixmap;
}

QVariant ShapeItem::itemChange(GraphicsItemChange change, const QVariant &value){
    if (change == QGraphicsItem::ItemTransformOriginPointChange && scene()) {
        QPointF center = boundingRect().center();
        return center;
    }
    return QGraphicsPolygonItem::itemChange(change, value);
}

void ShapeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    //Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(QPen(color));
    painter->setBrush(color);
    painter->setPen(QPen(Qt::black, 5));
    painter->drawPolygon(polygon());
    if (option->state & QStyle::State_Selected) {
        painter->setPen(Qt::blue);
        painter->setBrush(Qt::NoBrush);
        painter->drawRect(boundingRect());
    }
}

void ShapeItem::setColor(const QColor &newColor)
{
    // Store the original color for undo
    originalColor = color;
    // Set the new color
    color = newColor;
    // Update the shape's appearance
    update();
}

void ShapeItem::rotateAroundCenter(qreal angle)
{
    // Get the bounding rectangle of the shape
    QRectF boundingRect = this->boundingRect();
    // Calculate the center point of the bounding rect
    QPointF center = boundingRect.center();
    // Set the rotation origin to the center point
    this->setTransformOriginPoint(center);
    // Apply the rotation
    this->setRotation(this->rotation() + angle);
}
