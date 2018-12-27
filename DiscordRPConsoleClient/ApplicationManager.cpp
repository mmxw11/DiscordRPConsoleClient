#include "pch.h"

#include "ApplicationManager.h"
#include "StringUtils.h"

ApplicationManager::ApplicationManager() :
    commandManager(*this) {
}

void ApplicationManager::runApplication() {
    if (running) {
        return;
    }
    commandManager.registerCommands();
    this->running = true;
    while (running) {
        std::cout << "Command: ";
        std::string commandLineInput;
        std::getline(std::cin, commandLineInput);
        sutils::trim(commandLineInput);
        if (commandLineInput.empty()) {
            // just ignore...
            continue;
        }
        bool found = commandManager.dispatchCommand(commandLineInput);
        if (!found) {
            std::cout << "'" << commandLineInput << "' is not a recognized command, \nUse help command to see a list of available commands.\n" << std::endl;
        } else {
            std::cout << std::endl;
        }
    }
}

void ApplicationManager::shutdown() {
    this->running = false;
}

CommandManager& ApplicationManager::getCommandManager() {
    return commandManager;
}