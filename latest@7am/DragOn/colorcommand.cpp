#include "colorcommand.h"

ColorCommand::ColorCommand(ShapeItem *item, const QColor &oldColor, const QColor &newColor)
    : item(item), oldColor(oldColor), newColor(newColor) {}

void ColorCommand::undo() {
    // Push the current color to the stack before undoing
    colorStack.push(item->getColor());
    item->setColor(oldColor);
}

void ColorCommand::redo() {
    // Push the current color to the stack before redoing
    colorStack.push(item->getColor());
    item->setColor(newColor);
}
