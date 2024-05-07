#ifndef ADDSHAPECOMMAND_H
#define ADDSHAPECOMMAND_H

#include "Command.h"
#include "dragonscene.h"
#include "shapeitem.h"

class AddShapeCommand : public Command {
public:
    AddShapeCommand(ShapeItem * item, DragOnScene * scene);

    void undo() override;
    void redo() override;

private:
    ShapeItem * item;
    DragOnScene * scene;
};

#endif // ADDSHAPECOMMAND_H
