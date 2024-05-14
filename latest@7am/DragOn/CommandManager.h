#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H

#include "Command.h"

class CommandManager {

public:

    static CommandManager *instance();
    void executeCommand(Command * command);
    void undo();
    void redo();
    bool canUndo() const;
    bool canRedo() const;

private:
    CommandManager();
    ~CommandManager();
    static CommandManager *single_instance;

    QUndoStack undoStack;
};

#endif // COMMANDMANAGER_H
