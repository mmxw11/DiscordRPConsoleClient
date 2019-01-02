#pragma once

#include "ICommand.h"

class PartySizeCommand : public ICommand {

public:
    PartySizeCommand() :
        ICommand("partysize", "Set the user's party size. (\"10 of 10\", \"5 of 8\")") {
        addArgument("set/reset", true);
        addArgument("partySize", false);
        addArgument("partyMax", false);
    }
    void executeCommand(std::string* args, unsigned argsLength) override;
};