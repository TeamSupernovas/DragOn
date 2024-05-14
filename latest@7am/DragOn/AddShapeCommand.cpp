#include "AddShapeCommand.h"

AddShapeCommand::AddShapeCommand(ShapeItem* item, DragOnScene * scene) : item(item), scene(scene) {
    setText("Add Shape Item");
}

void AddShapeCommand::undo() {
    scene->removeItem(item);
}

void AddShapeCommand::redo() {
    scene->addItem(item);
}
