#include "ChangeTextColorCommand.h"

ChangeTextColorCommand::ChangeTextColorCommand(DiagramTextItem* item, QColor color)
    : item(item), prevColor(color) {
    setText("Change text font");
}

void ChangeTextColorCommand::undo() {
    swap();
}

void ChangeTextColorCommand::redo() {
    swap();
}

void ChangeTextColorCommand::swap() {
    QColor color = item->defaultTextColor();
    item->setDefaultTextColor(prevColor);
    prevColor = color;
}


