#ifndef SHAPEFACTORY_H
#define SHAPEFACTORY_H


#include <QVariantMap>
#include <QGraphicsItem>

#include "ShapeItem.h"

typedef struct ShapeParameters {
    QVariantMap params;
} ShapeParameters;

class ShapeFactory {

public:
    static QPolygonF createShapePolygon(ShapeType shapeType, QPointF size);
    static ShapeItem* createShape(ShapeType shapeType, const ShapeParameters& params);
    static ShapeItem* createDefaultShape(ShapeType shapeType);
};

#endif // SHAPEFACTORY_H
