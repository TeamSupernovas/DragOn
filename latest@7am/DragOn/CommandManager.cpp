#include "CommandManager.h"

CommandManager::CommandManager() {}

CommandManager::~CommandManager() {}

void CommandManager::executeCommand(Command * command) {
    undoStack.push(command);// executes the command and then pushes it on the stack
}

void CommandManager::undo() {
    if (canUndo()) {
        undoStack.undo();
    }
}

void CommandManager::redo() {
    if (canRedo()) {
        undoStack.redo();
    }
}

bool CommandManager::canUndo() const {
    return undoStack.canUndo();
}

bool CommandManager::canRedo() const {
    return undoStack.canRedo();
}
