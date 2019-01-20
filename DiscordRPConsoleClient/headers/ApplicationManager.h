#pragma once

#include <atomic>
#include <future>
#include <queue>
#include <mutex>
#include "CommandManager.h"
#include "DiscordHandler.h"

class ApplicationManager {

public:
    ApplicationManager();
    ApplicationManager(const ApplicationManager&) = delete;
    ApplicationManager& operator=(const ApplicationManager&) = delete;
    ~ApplicationManager();
    void addInputRequest(std::promise<std::string>& promise);
    void runApplication(const std::string& applicationId);
    void shutdown();
    CommandManager& getCommandManager();
private:
    void runConsoleInputReaderLoop();
    std::atomic<bool> running;
    CommandManager commandManager;
    DiscordHandler& discordHandler;
    std::mutex inputQueueMutex;
    std::queue<std::promise<std::string>*> inputQueue;
};