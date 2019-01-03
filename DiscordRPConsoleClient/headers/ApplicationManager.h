#pragma once

#include <atomic>
#include "CommandManager.h"
#include "DiscordHandler.h"

class ApplicationManager {

public:
    ApplicationManager();
    ApplicationManager(const ApplicationManager&) = delete;
    ApplicationManager& operator=(const ApplicationManager&) = delete;
    ~ApplicationManager();
    void runApplication(const std::string& applicationId);
    void shutdown();
    CommandManager& getCommandManager();
private:
    void runConsoleInputLoop();
    std::atomic<bool> running;
    CommandManager commandManager;
    DiscordHandler& discordHandler;
};