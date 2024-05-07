#include<MoveCommand.h>

MoveCommand::MoveCommand(QGraphicsItem * item, QPointF moveBy)
    : item(item), moveBy(moveBy) {
    setText("Move Item");

}

void MoveCommand::undo() {
    item->setPos(item->scenePos() - moveBy);
}

void MoveCommand::redo() {

    item->setPos(item->scenePos() + moveBy);
}
