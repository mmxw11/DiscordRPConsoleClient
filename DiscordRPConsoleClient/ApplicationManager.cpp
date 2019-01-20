#include "pch.h"

#include "ApplicationManager.h"
#include "StringUtils.h"
#include <thread>
#include <assert.h>

// Ignore function definition not found warning. (linker will take care of this later on...)
extern "C" void Discord_RunCallbacks();

ApplicationManager::ApplicationManager() :
    running(false),
    commandManager(*this),
    discordHandler(DiscordHandler::getInstance()) {
    commandManager.registerCommands();
}

ApplicationManager::~ApplicationManager() {
    shutdown();
}

void ApplicationManager::addInputRequest(std::promise<std::string>& promise) {
    std::unique_lock<std::mutex> ulock(inputQueueMutex);
    inputQueue.push(&promise);
    ulock.unlock();
}

void ApplicationManager::runApplication(const std::string& applicationId) {
    if (running) {
        return;
    }
    discordHandler.setApplicationId(applicationId);
    bool success = discordHandler.initialize();
    assert(success);
    this->running = true;
    // Start console input reader thread.
    std::thread consoleThread(&ApplicationManager::runConsoleInputReaderLoop, this);
    // Discord callbacks.
    while (running) {
        const DiscordHandler::State& handlerState = discordHandler.getHandlerState();
        if (handlerState == DiscordHandler::State::UNINITIALIZED) {
            continue;
        }
        if (discordHandler.isCallbackUpdate()) {
            Discord_RunCallbacks();
        }
    }
    std::cin.putback('\n'); // Push a new line character into the buffer. triggers getline if needed.
    consoleThread.join();
}

void ApplicationManager::runConsoleInputReaderLoop() {
    while (running) {
        if (discordHandler.getHandlerState() == DiscordHandler::State::INITIALIZED) {
            std::this_thread::sleep_for(std::chrono::seconds(2));
            continue;
        }
        std::string commandLineInput;
        std::getline(std::cin, commandLineInput);
        if (!std::cin.good()) {
            // Unexpected input. (ctrl + c/break for example)
            std::cin.clear();
            shutdown();
            break;
        }
        sutils::trim(commandLineInput);
        // Check queue.
        std::unique_lock<std::mutex> ulock(inputQueueMutex);
        if (!inputQueue.empty()) {
            std::promise<std::string>* promise = inputQueue.front();
            inputQueue.pop();
            promise->set_value(commandLineInput);
            ulock.unlock();
            continue;
        }
        ulock.unlock();
        if (commandLineInput.empty()) {
            // Just ignore...
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