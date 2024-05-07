#include<MoveCommand.h>

MoveCommand::MoveCommand(QGraphicsItem * item, QPointF moveBy)
    : item(item), moveBy(moveBy) {
    setText("Move Item");

}

void MoveCommand::undo() {
    qDebug() << "MoveCommand undo: " << item->scenePos() << "-" << moveBy;
    item->setPos(item->scenePos() - moveBy);
}

void MoveCommand::redo() {
    qDebug() << "MoveCommand redo: " << item->scenePos() << "+" << moveBy;
    item->setPos(item->scenePos() + moveBy);
}
