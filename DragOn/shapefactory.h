#ifndef SHAPEFACTORY_H
#define SHAPEFACTORY_H


#include <QVariantMap>
#include <QGraphicsItem>

#include "shapeitem.h"

typedef struct ShapeParameters {
    QVariantMap params;
} ShapeParameters;

class ShapeFactory
{

public:
    static ShapeItem* createShape(ShapeType shapeType, const ShapeParameters& params);
    static ShapeItem* createDefaultShape(ShapeType shapeType);
};

#endif // SHAPEFACTORY_H
