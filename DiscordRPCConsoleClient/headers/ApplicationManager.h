#pragma once

#include "CommandManager.h"

class ApplicationManager {

public:
    ApplicationManager();
    CommandManager& getCommandManager();
private:
    CommandManager commandManager;
};