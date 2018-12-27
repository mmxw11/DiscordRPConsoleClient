#pragma once

#include "CommandManager.h"

class ApplicationManager {

public:
    ApplicationManager();
    ApplicationManager(const ApplicationManager&) = delete;
    ApplicationManager& operator=(const ApplicationManager&) = delete;
    void runApplication();
    void shutdown();
    CommandManager& getCommandManager();
private:
    bool running;
    CommandManager commandManager;
};