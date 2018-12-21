#pragma once

#include "ICommand.h" 

class TestCmd : public ICommand {

public:
    TestCmd(std::string commandName) :
        ICommand(commandName, "Sample description") {
        addArgument("test", false);
        addArgument("test2", true);
    }
    void executeCommand(unsigned argsCount, std::string* args) override;
};