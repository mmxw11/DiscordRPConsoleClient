#pragma once

#include "ICommand.h"

class SetUserStatusCommand : public ICommand {

public:
    SetUserStatusCommand();
    void executeCommand(std::string* args, unsigned argsLength) override;
};