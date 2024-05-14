#ifndef CHANGETEXTCOLORCOMMAND_H
#define CHANGETEXTCOLORCOMMAND_H

#include <QColor>

#include "Command.h"
#include "TextItem.h"

class ChangeTextColorCommand: public Command {

public:
    ChangeTextColorCommand(TextItem * item, QColor font);
    void undo() override;
    void redo() override;

protected:
    void swap();

private:
    TextItem * item;
    QColor prevColor;
};

#endif // CHANGETEXTCOLORCOMMAND_H
