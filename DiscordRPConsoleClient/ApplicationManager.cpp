#include "pch.h"

#include "ApplicationManager.h"
#include "StringUtils.h"
#include <thread>
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
    // start console input thread.
    std::thread consoleThread(&ApplicationManager::runConsoleInputLoop, this);
    // discord callbacks.
    while (running) {
        const DiscordHandler::State& handlerState = discordHandler.getHandlerState();
        if (handlerState == DiscordHandler::State::UNINITIALIZED) {
            continue;
        }
        if (discordHandler.isCallbackUpdate()) {
            Discord_RunCallbacks();
        }
    }
    std::cin.putback('\n'); // push a new line character into the buffer. triggers getline if needed.
    consoleThread.join();
}

void ApplicationManager::runConsoleInputLoop() {
    while (running) {
        if (discordHandler.getHandlerState() == DiscordHandler::INITIALIZED) {
            std::this_thread::sleep_for(std::chrono::seconds(2));
            continue;
        }
        std::string commandLineInput;
        std::getline(std::cin, commandLineInput);
        if (!std::cin.good()) {
            // unexpected input (ctrl + c/break for example)
            std::cin.clear();
            shutdown();
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
            std::cout << "'" << commandLineInput << "' is not a recognized command, \nUse \"HELP\" command to see a list of available commands." << std::endl;
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