#ifndef MOVECOMMAND_H
#define MOVECOMMAND_H

#include "Command.h"
#include "shapeitem.h"

class MoveCommand : public Command {
public:
    MoveCommand(ShapeItem * item, QPointF moveBy);

    void undo() override;
    void redo() override;

private:
    ShapeItem * item;
    QPointF moveBy;

};

#endif // MOVECOMMAND_H
