#pragma once

#include "ICommand.h"
#include "ApplicationManager.h"

class ExitCommand : public ICommand {

public:
    ExitCommand() :
        ICommand("exit", "Exit the application.") {
    }

    void executeCommand(std::string* args, unsigned argsLength) override {
        extern ApplicationManager* appManagerInstance;
        appManagerInstance->shutdown();
    }
};