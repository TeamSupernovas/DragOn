#include "ShapeFactory.h"


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
    QRectF rect = params.params.value("line").toRectF();
    QPolygonF polygon;
    polygon << QPointF(rect.left(), rect.top())
            << QPointF(rect.right(), rect.bottom());
    return polygon;
}

QPolygonF createCirclePolygon(const ShapeParameters& params) {
    QRectF rect = params.params.value("circle").toRectF();
    QPolygonF polygon;
    const int points = 32;
    for(int i = 0; i < points; ++i) {
        qreal angle = 2 * M_PI * i / points;
        polygon << QPointF(rect.center().x() + rect.width()/2 * cos(angle),
                rect.center().y() + rect.height()/2 * sin(angle));
    }
    polygon << polygon.first(); // close the circle
    return polygon;
}

QPolygonF createTrianglePolygon(const ShapeParameters& params) {
    QRectF rect = params.params.value("triangle").toRectF();
    QPolygonF polygon;
    polygon << QPointF(rect.left(), rect.bottom())
            << QPointF(rect.right(), rect.bottom())
            << QPointF(rect.center().x(), rect.top());
    polygon << polygon.first(); // Close the triangle
    return polygon;
}

QPolygonF createSquarePolygon(const ShapeParameters& params) {
    QRectF rect = params.params.value("square").toRectF();
    QPolygonF polygon;
    polygon << QPointF(rect.left(), rect.top())
            << QPointF(rect.right(), rect.top())
            << QPointF(rect.right(), rect.bottom())
            << QPointF(rect.left(), rect.bottom())
            << QPointF(rect.left(), rect.top()); // Close the square
    return polygon;
}

QPolygonF createPentagonPolygon(const ShapeParameters& params) {
    QRectF rect = params.params.value("pentagon").toRectF();
    QPolygonF polygon;
    const int points = 5; // Pentagon has 5 sides
    qreal angle = 0;
    qreal angleIncrement = 2 * M_PI / points;
    for (int i = 0; i < points; ++i) {
        polygon << QPointF(rect.center().x() + rect.width() / 2 * cos(angle),
                           rect.center().y() + rect.height() / 2 * sin(angle));
        angle += angleIncrement;
    }
    polygon << polygon.first(); // Close the pentagon
    return polygon;
}

QPolygonF createRhombusPolygon(const ShapeParameters& params) {
    QRectF rect = params.params.value("rhombus").toRectF();
    QPolygonF polygon;
    polygon << QPointF(rect.center().x(), rect.top())
            << QPointF(rect.right(), rect.center().y())
            << QPointF(rect.center().x(), rect.bottom())
            << QPointF(rect.left(), rect.center().y())
            << QPointF(rect.center().x(), rect.top()); // Close the rhombus
    return polygon;
}


QPolygonF ShapeFactory::createShapePolygon(ShapeType shapeType, QPointF size) {
    ShapeParameters shapeParams;
    switch (shapeType) {
    case ShapeType::Rectangle:
        shapeParams.params.insert("rect", QRectF(0, 0, size.rx(), size.ry()));
        return createRectanglePolygon(shapeParams);

    case ShapeType::Line:
        shapeParams.params.insert("line", QRectF(0, 0, size.rx(), size.ry()));
        return createLinePolygon(shapeParams);

    case ShapeType::Circle:
        shapeParams.params.insert("circle", QRectF(0, 0, size.rx(), size.ry()));
        return createCirclePolygon(shapeParams);

    case ShapeType::Triangle:
        shapeParams.params.insert("triangle", QRectF(0, 0, size.rx(), size.ry()));
        return createTrianglePolygon(shapeParams);

    case ShapeType::Square:
        shapeParams.params.insert("square", QRectF(0, 0, size.rx(), size.ry()));
        return createSquarePolygon(shapeParams);

    case ShapeType::Pentagon:
        shapeParams.params.insert("pentagon", QRectF(0, 0, size.rx(), size.ry()));
        return createPentagonPolygon(shapeParams);

    case ShapeType::Rhombus:
        shapeParams.params.insert("rhombus", QRectF(0, 0, size.rx(), size.ry()));
        return createRhombusPolygon(shapeParams);
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
    case ShapeType::Square:
        polygon = createSquarePolygon(params);
        break;
    case ShapeType::Triangle:
        polygon = createTrianglePolygon(params);
        break;
    case ShapeType::Pentagon:
        polygon = createPentagonPolygon(params);
        break;
    case ShapeType::Rhombus:
        polygon = createRhombusPolygon(params);
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
        shapeParams.params.insert("line", QRectF(0, 0, 64, 64));
        return createShape(shapeType, shapeParams);

    case ShapeType::Circle:
        shapeParams.params.insert("circle", QRectF(0, 0, 128, 128));
        return createShape(shapeType, shapeParams);

    case ShapeType::Triangle:
        shapeParams.params.insert("triangle", QRectF(0, 0, 100, 100));
        return createShape(ShapeType::Triangle, shapeParams);

    case ShapeType::Square:
        shapeParams.params.insert("square", QRectF(0, 0, 100, 100));
        return createShape(ShapeType::Square, shapeParams);

    case ShapeType::Pentagon:
        shapeParams.params.insert("pentagon", QRectF(0, 0, 100, 100));
        return createShape(ShapeType::Pentagon, shapeParams);

    case ShapeType::Rhombus:
        shapeParams.params.insert("rhombus", QRectF(0, 0, 100, 100));
        return createShape(ShapeType::Rhombus, shapeParams);
    }
    return nullptr;
}


