#include "ChangeShapeColorCommand.h"

ChangeShapeColorCommand::ChangeShapeColorCommand(ShapeItem *item, QColor color)
    : item(item), prevColor(color) {
    setText("Change text color");
}

void ChangeShapeColorCommand::undo() {
    swap();
}

void ChangeShapeColorCommand::redo() {
    swap();
}

void ChangeShapeColorCommand::swap() {
    QColor color = item->getColor();
    item->setColor(prevColor);
    prevColor = color;
}
