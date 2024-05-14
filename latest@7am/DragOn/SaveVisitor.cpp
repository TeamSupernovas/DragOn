#include "SaveVisitor.h"
#include "PolygonSerializer.h"
#include "TransformSerializer.h"
#include "ColorSerializer.h"
#include "FontSerializer.h"

void SaveVisitor::visitShapeItem(ShapeItem *item) {
    out << "ShapeItem::" << static_cast<int>(item->getShapeType()) << "::"
        << PolygonSerializer::serialize(item->polygon()) << "::"
        << TransformSerializer::serialize(item->sceneTransform()) << "::"
        << ColorSerializer::serialize(item->getColor()) << "\n";
}

void SaveVisitor::visitTextItem(TextItem *item) {
    out << "TextItem::" << QString::fromUtf8(item->toPlainText().toUtf8().toBase64()) << "::"
        << FontSerializer::serialize(item->font()) << "::"
        << ColorSerializer::serialize(item->defaultTextColor()) << "::"
        << TransformSerializer::serialize(item->sceneTransform()) << "\n";
}
