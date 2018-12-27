#pragma once

#include "ICommand.h"

class TestCmd : public ICommand {

public:
    TestCmd(ApplicationManager& appManager, std::string commandName) :
        ICommand(appManager, commandName, "Sample description") {
        addArgument("test", false);
        addArgument("test2", true);
    }

    void executeCommand(std::string* args, unsigned argsLength) override;
};