#include "pch.h"

#include "ApplicationManager.h"
#include "StringUtils.h"
#include <assert.h>

// Ignore function definition not found warning. (linker will take care of this later on...)
extern "C" void Discord_RunCallbacks();

ApplicationManager::ApplicationManager() :
    commandManager(*this),
    discordHandler(DiscordHandler::getInstance()) {
}

ApplicationManager::~ApplicationManager() {
    shutdown();
}

void ApplicationManager::runApplication() {
    if (running) {
        return;
    }
    commandManager.registerCommands();
    bool success = discordHandler.initialize(); //TODO: HARDCODED VALUE
    assert(success);
    this->running = true;
    while (running) {
        // update discord stuff.
        DiscordHandler::State handlerState = discordHandler.getHandlerState();
        if (handlerState != DiscordHandler::State::UNINITIALIZED) {
            if (discordHandler.isCallbackUpdate()) {
                Discord_RunCallbacks();
            }
            if (handlerState == DiscordHandler::State::INITIALIZED) {
                continue;
            }
        }
        // commands.
        std::string commandLineInput;
        std::getline(std::cin, commandLineInput);
        if (!std::cin.good()) {
            // unexpected input (ctrl + c/break for example)
            std::cin.clear();
            break;
        }
        sutils::trim(commandLineInput);
        if (commandLineInput.empty()) {
            // just ignore...
            continue;
        }
        std::cout << std::endl;
        bool found = commandManager.dispatchCommand(commandLineInput);
        if (!found) {
            std::cout << "'" << commandLineInput << "' is not a recognized command, \nUse help command to see a list of available commands." << std::endl;
        }
    }
}

void ApplicationManager::shutdown() {
    if (!running) {
        return;
    }
    this->running = false;
    discordHandler.uninitialize();
}

CommandManager& ApplicationManager::getCommandManager() {
    return commandManager;
}

DiscordHandler& ApplicationManager::getDiscordHandler() {
    return discordHandler;
}
