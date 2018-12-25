#pragma once

#include "CommandManager.h"

class ApplicationManager {

public:
    ApplicationManager();
    void runApplication();
    CommandManager& getCommandManager();
private:
    CommandManager commandManager;
};