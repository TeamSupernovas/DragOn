#ifndef ADDTEXTCOMMAND_H
#define ADDTEXTCOMMAND_H

#include "Command.h"
#include "dragonscene.h"
#include  "diagramtextitem.h"

class AddTextCommand : public Command
{
public:
    AddTextCommand(DiagramTextItem * item, DragOnScene * scene);
    void undo() override;
    void redo() override;

private:
    DiagramTextItem * item;
    DragOnScene * scene;
};

#endif // ADDTEXTCOMMAND_H
