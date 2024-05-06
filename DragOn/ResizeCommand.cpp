#include "ResizeCommand.h"

#include "shapefactory.h"

ResizeCommand::ResizeCommand(ShapeItem * item, QPointF changeBoundingRectSizeBy):
    item(item), changeBoundingRectSizeBy(changeBoundingRectSizeBy) {}

void ResizeCommand::undo(){
    QPointF oldBoundingRectSize = item->polygon().boundingRect().bottomRight() - item->polygon().boundingRect().topLeft()  - changeBoundingRectSizeBy;
    QPolygonF polygon = ShapeFactory::createShapePolygon(item->getShapeType(), oldBoundingRectSize);
    item->setPolygon(polygon);
}
void ResizeCommand::redo() {
    QPointF newBoundingRectSize = item->polygon().boundingRect().bottomRight() - item->polygon().boundingRect().topLeft() + changeBoundingRectSizeBy;
    QPolygonF polygon = ShapeFactory::createShapePolygon(item->getShapeType(), newBoundingRectSize);
    item->setPolygon(polygon);
}
