#pragma once

#include "ICommand.h"

class StateCommand : public ICommand {

public:
    StateCommand();
    void executeCommand(std::string* args, unsigned argsLength) override;
};