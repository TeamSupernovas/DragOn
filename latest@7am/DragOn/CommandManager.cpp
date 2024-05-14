#include "CommandManager.h"

CommandManager * CommandManager::single_instance = nullptr;

CommandManager::CommandManager() {}

CommandManager::~CommandManager() {
    single_instance = nullptr;
}

CommandManager *CommandManager::instance() {
    if (single_instance == nullptr) {
        single_instance = new CommandManager();
    }

    return single_instance;
}

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
