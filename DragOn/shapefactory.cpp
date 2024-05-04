#include "shapefactory.h"


ShapeItem* ShapeFactory::createShape(ShapeType shapeType, const ShapeParameters& params, QGraphicsItem* parent) {
    switch (shapeType) {
    case ShapeType::Rectangle:
        return createRectangle(shapeType, params, parent);
    default:
        return nullptr;
    }
}

ShapeItem* ShapeFactory::createRectangle(ShapeType shapeType, const ShapeParameters& params, QGraphicsItem* parent) {
    QRectF rect = params.params.value("rect").toRectF();
    QPolygonF polygon;
    polygon << QPointF(rect.left(), rect.top())
            << QPointF(rect.right(), rect.top())
            << QPointF(rect.right(), rect.bottom())
            << QPointF(rect.left(), rect.bottom())
            << QPointF(rect.left(), rect.top());
    return new ShapeItem(shapeType, polygon, parent);
}

