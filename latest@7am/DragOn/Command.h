#ifndef COMMAND_H
#define COMMAND_H

#include <QUndoCommand>

class Command : public QUndoCommand {
public:
    Command();
    virtual ~Command() {}

    virtual void undo() override = 0;
    virtual void redo() override = 0;

};

#endif // COMMAND_H
