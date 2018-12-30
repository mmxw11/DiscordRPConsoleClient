#pragma once

#include "ICommand.h"
#include "ApplicationManager.h"

class ExitCommand : public ICommand {

public:
    ExitCommand(ApplicationManager* appManager) :
        ICommand(appManager, "exit", "Exit the application.") {
    }

    void executeCommand(std::string* args, unsigned argsLength) override {
        appManager->shutdown();
    }
};