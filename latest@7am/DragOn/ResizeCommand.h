#ifndef RESIZECOMMAND_H
#define RESIZECOMMAND_H

#include "Command.h"
#include "ShapeItem.h"

#include <QPointF>

class ResizeCommand : public Command
{
public:
    ResizeCommand(ShapeItem * item, QPointF changeBoundingRectSizeBy);

    void undo() override;
    void redo() override;

private:
    ShapeItem * item;
    QPointF changeBoundingRectSizeBy;

};

#endif // RESIZECOMMAND_H
