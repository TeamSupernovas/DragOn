#include "ChangeTextFontCommand.h"

ChangeTextFontCommand::ChangeTextFontCommand(TextItem* item, QFont font)
    : item(item), prevFont(font) {
    setText("Change text font");
}

void ChangeTextFontCommand::undo() {
    swap();
}

void ChangeTextFontCommand::redo() {
    swap();
}

void ChangeTextFontCommand::swap() {
    QFont font = item->font();
    item->setFont(prevFont);
    prevFont = font;
}


