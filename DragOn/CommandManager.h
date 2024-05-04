#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H

#include "Command.h"

class CommandManager {
public:
    CommandManager();
    ~CommandManager();

    void executeCommand(Command * command);
    void undo();
    void redo();
    bool canUndo() const;
    bool canRedo() const;

private:
    QUndoStack undoStack;
};

#endif // COMMANDMANAGER_H
