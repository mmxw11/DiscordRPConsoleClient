#pragma once

#include "ICommand.h"

class ClearPresenceCommand : public ICommand {

public:
    ClearPresenceCommand();
    void executeCommand(std::string* args, unsigned argsLength) override;
};