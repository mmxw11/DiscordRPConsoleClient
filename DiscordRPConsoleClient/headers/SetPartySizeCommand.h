#pragma once

#include "ICommand.h"

class SetPartySizeCommand : public ICommand {

public:
    SetPartySizeCommand();
    void executeCommand(std::string* args, unsigned argsLength) override;
};