#pragma once

#include "ICommand.h"

class ClearPresenceCommand : public ICommand {

public:
    ClearPresenceCommand() :
        ICommand("clearpresence", "Clear presence information.") {
    }
    void executeCommand(std::string* args, unsigned argsLength) override;
};