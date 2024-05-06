#ifndef MOVECOMMAND_H
#define MOVECOMMAND_H

#include "Command.h"
#include "dragonscene.h"
#include "shapeitem.h"

class MoveCommand : public Command {
public:
    MoveCommand(ShapeItem * item, DragOnScene * scene, QPointF moveBy);

    void undo() override;
    void redo() override;

private:
    ShapeItem * item;
    DragOnScene * scene;
    QPointF moveBy;

};

#endif // MOVECOMMAND_H
