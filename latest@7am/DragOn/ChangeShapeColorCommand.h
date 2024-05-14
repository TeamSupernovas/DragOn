#ifndef CHANGESHAPECOLORCOMMAND_H
#define CHANGESHAPECOLORCOMMAND_H

#include <QColor>
#include <QStack>

#include "Command.h"
#include "ShapeItem.h"

class ChangeShapeColorCommand : public Command {

public:
    ChangeShapeColorCommand(ShapeItem *item, QColor color);

    void undo() override;
    void redo() override;

protected:
    void swap();

private:
    ShapeItem *item;
    QColor prevColor;
};

#endif // CHANGESHAPECOLORCOMMAND_H
