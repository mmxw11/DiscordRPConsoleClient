#pragma once

#include "ICommand.h"

class PartySizeCommand : public ICommand {

public:
    PartySizeCommand();
    void executeCommand(std::string* args, unsigned argsLength) override;
};