#ifndef ROTATECOMMAND_H
#define ROTATECOMMAND_H

#include "Command.h"
#include "ShapeItem.h"

class RotateCommand : public Command {

public:
    RotateCommand(ShapeItem *item, qreal angle);
    void undo() override;
    void redo() override;

private:
    ShapeItem *item;
    qreal oldRotation;
    qreal newRotation;
};

#endif // ROTATECOMMAND_H
