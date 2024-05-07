#ifndef COLORCOMMAND_H
#define COLORCOMMAND_H

#include "Command.h"
#include "shapeitem.h"

#include <QColor>
#include <QStack>

class ColorCommand : public Command
{
public:
    ColorCommand(ShapeItem *item, const QColor &oldColor, const QColor &newColor);

    void undo() override;
    void redo() override;

private:
    ShapeItem *item;
    QColor oldColor;
    QColor newColor;
    QStack<QColor> colorStack; // Stack to keep track of color changes
};

#endif // COLORCOMMAND_H
