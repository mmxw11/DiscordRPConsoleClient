#pragma once

#include "ICommand.h"

class StateCommand : public ICommand {

public:
    StateCommand() :
        ICommand("state", "Set the user's current party status. (\"Looking to Play\", \"Playing Solo\", \"In a Group\")") {
        addArgument("state/reset", true);
    }
    void executeCommand(std::string* args, unsigned argsLength) override;
};