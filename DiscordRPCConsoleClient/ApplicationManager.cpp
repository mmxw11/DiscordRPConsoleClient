#include "pch.h"

#include "ApplicationManager.h"

ApplicationManager::ApplicationManager() :
    commandManager(*this) {
}

CommandManager& ApplicationManager::getCommandManager() {
    return commandManager;
}