#include "ChangeTextColorCommand.h"

ChangeTextColorCommand::ChangeTextColorCommand(TextItem* item, QColor color) : item(item), prevColor(color) {
    setText("Change text color");
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


