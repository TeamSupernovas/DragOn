#include "AddCommand.h"

AddCommand::AddCommand(ShapeItem* item, DragOnScene * scene)
    : item(item), scene(scene) {
    setText("Add Item");

}

void AddCommand::undo() {
    scene->removeItem(item);
}

void AddCommand::redo() {
    scene->addItem(item);
}
