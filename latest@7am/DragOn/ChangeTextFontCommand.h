#ifndef CHANGETEXTFONTCOMMAND_H
#define CHANGETEXTFONTCOMMAND_H

#include <QFont>

#include "Command.h"
#include "TextItem.h"

class ChangeTextFontCommand: public Command
{
public:
    ChangeTextFontCommand(TextItem * item, QFont font);
    void undo() override;
    void redo() override;

protected:
    void swap();

private:
    TextItem * item;
    QFont prevFont;
};

#endif // CHANGETEXTFONTCOMMAND_H
