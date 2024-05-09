#include "AddTextCommand.h"

AddTextCommand::AddTextCommand(TextItem* item, DragOnScene * scene)
    : item(item), scene(scene) {
    setText("Add Text Item");

}

void AddTextCommand::undo() {
    scene->removeItem(item);
}

void AddTextCommand::redo() {
    scene->addItem(item);
}
