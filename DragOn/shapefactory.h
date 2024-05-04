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
    static ShapeItem* createShape(ShapeType shapeType, const ShapeParameters& params, QGraphicsItem* parent = nullptr);


private:
    static ShapeItem* createRectangle(ShapeType shapeType, const ShapeParameters& params, QGraphicsItem* parent= nullptr);

};

#endif // SHAPEFACTORY_H
