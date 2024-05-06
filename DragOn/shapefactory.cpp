#include "shapefactory.h"


QPolygonF createRectanglePolygon(const ShapeParameters& params) {
    QRectF rect = params.params.value("rect").toRectF();
    QPolygonF polygon;
    polygon << QPointF(rect.left(), rect.top())
            << QPointF(rect.right(), rect.top())
            << QPointF(rect.right(), rect.bottom())
            << QPointF(rect.left(), rect.bottom())
            << QPointF(rect.left(), rect.top());
    return polygon;
}

QPolygonF createLinePolygon(const ShapeParameters& params) {
    QRectF rect = params.params.value("rect").toRectF();
    QPolygonF polygon;
    polygon << QPointF(rect.left(), rect.top())
            << QPointF(rect.right(), rect.bottom());
    return polygon;
}

QPolygonF createCirclePolygon(const ShapeParameters& params) {
    QRectF rect = params.params.value("rect").toRectF();
    QPolygonF polygon; // Similar to previous circle implementation
    const int points = 32;  // Example points count
    for(int i = 0; i < points; ++i) {
        qreal angle = 2 * M_PI * i / points;
        polygon << QPointF(rect.center().x() + rect.width()/2 * cos(angle),
                           rect.center().y() + rect.height()/2 * sin(angle));
    }
    polygon << polygon.first(); // Close the circle
    return polygon;
}

QPolygonF ShapeFactory::createShapePolygon(ShapeType shapeType, QPointF size) {
    ShapeParameters shapeParams;
    switch (shapeType) {
    case ShapeType::Rectangle:
        shapeParams.params.insert("rect", QRectF(0, 0, size.rx(), size.ry()));
        return createRectanglePolygon(shapeParams);

    case ShapeType::Line:
        shapeParams.params.insert("rect", QRectF(0, 0, size.rx(), size.ry()));
        return createLinePolygon(shapeParams);

    case ShapeType::Circle:
        shapeParams.params.insert("rect", QRectF(0, 0, size.rx(), size.ry()));
        return createCirclePolygon(shapeParams);


    }
    QPolygonF polygon;
    return polygon;
}


ShapeItem* ShapeFactory::createShape(ShapeType shapeType, const ShapeParameters& params) {
    QPolygonF polygon;
    switch (shapeType) {
    case ShapeType::Rectangle:
        polygon = createRectanglePolygon(params);
        break;
    case ShapeType::Line:
        polygon = createLinePolygon(params);
        break;
    case ShapeType::Circle:
        polygon = createCirclePolygon(params);
        break;
    }
    return new ShapeItem(shapeType, polygon);
}


ShapeItem* ShapeFactory::createDefaultShape(ShapeType shapeType) {
    ShapeParameters shapeParams;
    switch (shapeType) {
    case ShapeType::Rectangle:
        shapeParams.params.insert("rect", QRectF(0, 0, 128, 64));
        return createShape(shapeType, shapeParams);

    case ShapeType::Line:
        shapeParams.params.insert("rect", QRectF(0, 0, 64, 64));
        return createShape(shapeType, shapeParams);

    case ShapeType::Circle:
        shapeParams.params.insert("rect", QRectF(0, 0, 128, 128));
        return createShape(shapeType, shapeParams);
    }
    return nullptr;;
}


