#pragma once

#include "ICommand.h"

class DetailsCommand : public ICommand {

public:
    DetailsCommand();
    void executeCommand(std::string* args, unsigned argsLength) override;
};