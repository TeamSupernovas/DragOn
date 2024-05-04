#ifndef ADDCOMMAND_H
#define ADDCOMMAND_H

#include "Command.h"
#include "dragonscene.h"
#include "shapeitem.h"

class AddCommand : public Command {
public:
    AddCommand(ShapeItem * item, DragOnScene * scene);

    void undo() override;
    void redo() override;

private:
    ShapeItem * item;
    QGraphicsScene * scene;
};

#endif // ADDCOMMAND_H
