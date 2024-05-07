#ifndef CHANGETEXTCOLORCOMMAND_H
#define CHANGETEXTCOLORCOMMAND_H

#include "Command.h"
#include  "diagramtextitem.h"
#include <QColor>

class ChangeTextColorCommand: public Command
{
public:
    ChangeTextColorCommand(DiagramTextItem * item, QColor font);
    void undo() override;
    void redo() override;

protected:
    void swap();

private:
    DiagramTextItem * item;
    QColor prevColor;
};
#endif // CHANGETEXTCOLORCOMMAND_H
