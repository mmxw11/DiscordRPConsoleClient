#pragma once

#include "CommandManager.h"
#include "DiscordHandler.h"

class ApplicationManager {

public:
    ApplicationManager();
    ApplicationManager(const ApplicationManager&) = delete;
    ApplicationManager& operator=(const ApplicationManager&) = delete;
    ~ApplicationManager();
    void runApplication();
    void shutdown();
    CommandManager& getCommandManager();
    DiscordHandler& getDiscordHandler();
private:
    bool running;
    CommandManager commandManager;
    DiscordHandler discordHandler;
};