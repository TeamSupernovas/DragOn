#ifndef ADDTEXTCOMMAND_H
#define ADDTEXTCOMMAND_H

#include "Command.h"
#include "DragOnScene.h"
#include "TextItem.h"

class AddTextCommand : public Command {

public:
    AddTextCommand(TextItem * item, DragOnScene * scene);
    void undo() override;
    void redo() override;

private:
    TextItem * item;
    DragOnScene * scene;
};

#endif // ADDTEXTCOMMAND_H
