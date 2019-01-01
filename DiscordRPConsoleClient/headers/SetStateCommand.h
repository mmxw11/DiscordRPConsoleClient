#pragma once

#include "ICommand.h"

class SetStateCommand : public ICommand {

public:
    SetStateCommand();
    void executeCommand(std::string* args, unsigned argsLength) override;
};