#pragma once

#include "ICommand.h"

class HelpCommand : public ICommand {

public:
    HelpCommand(ApplicationManager* appManager) :
        ICommand(appManager, "help", "Display help about the commands.") {
        addArgument("command-name", false);
    }
    void executeCommand(std::string* args, unsigned argsLength) override;
};