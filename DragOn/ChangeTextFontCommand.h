#ifndef CHANGETEXTFONTCOMMAND_H
#define CHANGETEXTFONTCOMMAND_H

#include "Command.h"
#include  "diagramtextitem.h"
#include <QFont>

class ChangeTextFontCommand: public Command
{
public:
    ChangeTextFontCommand(DiagramTextItem * item, QFont font);
    void undo() override;
    void redo() override;

protected:
    void swap();

private:
    DiagramTextItem * item;
    QFont prevFont;
};

#endif // CHANGETEXTFONTCOMMAND_H
