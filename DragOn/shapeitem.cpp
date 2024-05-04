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
    QPixmap pixmap(250, 250);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setPen(QPen(Qt::black, 8));
    painter.translate(125, 125);
    painter.drawPolyline(polygon());
    return pixmap;
}

QVariant ShapeItem::itemChange(GraphicsItemChange change, const QVariant &value){
    return QGraphicsPolygonItem::itemChange(change, value);
}



