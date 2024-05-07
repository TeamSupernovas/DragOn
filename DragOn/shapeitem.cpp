#include "shapeitem.h"
#include <QPainter>

ShapeItem::ShapeItem(ShapeType shapeType, QPolygonF polygon, QGraphicsItem *parent)
    : QGraphicsPolygonItem(polygon, parent), shapeType(shapeType) {

    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
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
    painter.drawPolyline(polygon());

    return pixmap;
}


QVariant ShapeItem::itemChange(GraphicsItemChange change, const QVariant &value){
    return QGraphicsPolygonItem::itemChange(change, value);
}



