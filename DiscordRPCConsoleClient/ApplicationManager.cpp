#include "pch.h"

#include "ApplicationManager.h"
#include <iostream>
#include <string>

ApplicationManager::ApplicationManager() :
    commandManager(*this) {
}

void ApplicationManager::runApplication() {
    if (running) {
        return;
    }
    this->running = true;
    while (running) {
        std::cout << "Command: ";
        std::string commandInput;
        std::getline(std::cin, commandInput);
        if (commandInput.empty()) {
            // just ignore...
            continue;
        }
        bool found = commandManager.dispatchCommand(commandInput);
        if (!found) {
            std::cout << "'" << commandInput << "' is not a recognized command, \nUse help command for help.\n" << std::endl;
        }
    }
}

void ApplicationManager::shutdown() {
    this->running = false;
}

CommandManager& ApplicationManager::getCommandManager() {
    return commandManager;
}