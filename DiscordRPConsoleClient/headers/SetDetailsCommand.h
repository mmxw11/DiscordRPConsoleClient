#pragma once

#include "ICommand.h"

class SetDetailsCommand : public ICommand {

public:
    SetDetailsCommand();
    void executeCommand(std::string* args, unsigned argsLength) override;
};