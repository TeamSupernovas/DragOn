#include "RotateCommand.h"

RotateCommand::RotateCommand(ShapeItem *item, qreal angle)
    : item(item), oldRotation(item->rotation()), newRotation(item->rotation() + angle) {}

void RotateCommand::undo() {
    item->setRotation(oldRotation);
}

void RotateCommand::redo() {
    item->setRotation(newRotation);
}
