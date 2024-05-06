#include<MoveCommand.h>>

MoveCommand::MoveCommand(ShapeItem * item, DragOnScene * scene, QPointF moveBy)
    : item(item), scene(scene), moveBy(moveBy) {
    setText("Move Item");

}

void MoveCommand::undo() {
    item->setPos(item->scenePos() - moveBy);
}

void MoveCommand::redo() {

    item->setPos(item->scenePos() + moveBy);
}
