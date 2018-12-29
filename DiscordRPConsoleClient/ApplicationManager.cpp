#include "pch.h"

#include "ApplicationManager.h"
#include "StringUtils.h"

ApplicationManager::ApplicationManager() :
    commandManager(*this) {
}

ApplicationManager::~ApplicationManager() {
    shutdown();
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
        if (!std::cin.good()) {
            // unexpected input (ctrl + c/break for example)
            std::cin.clear();
            std::cout << std::endl;
            break;
        }
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
    if (!running) {
        return;
    }
    this->running = false;
    discordHandler.shutdown();
}

CommandManager& ApplicationManager::getCommandManager() {
    return commandManager;
}

DiscordHandler& ApplicationManager::getDiscordHandler() {
    return discordHandler;
}
