#include<MoveCommand.h>>

MoveCommand::MoveCommand(ShapeItem * item, DragOnScene * scene, QPointF newPos)
    : item(item), scene(scene), newPos(newPos) {
    setText("Move Item");

}

void MoveCommand::undo() {
    item->setPos(oldPos);
}

void MoveCommand::redo() {
    oldPos = item->pos();
    item->setPos(newPos);
}
