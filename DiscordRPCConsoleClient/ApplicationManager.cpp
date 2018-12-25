#include "pch.h"

#include "ApplicationManager.h"
#include "StringUtils.h"
#include <iostream>
#include <string>

ApplicationManager::ApplicationManager() :
    commandManager(*this) {
}

void ApplicationManager::runApplication() {
    while (true) {
        std::string command;
        std::getline(std::cin, command);
        if (sutils::equalsIgnoreCase(command, "exit")) {
            break;
        }
        std::cout << "Command: " << command << std::endl;
    }
}

CommandManager& ApplicationManager::getCommandManager() {
    return commandManager;
}