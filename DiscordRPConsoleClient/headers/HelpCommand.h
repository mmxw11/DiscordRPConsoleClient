#pragma once

#include "ICommand.h"

class HelpCommand : public ICommand {

public:
    HelpCommand(ApplicationManager* appManager);
    void executeCommand(std::string* args, unsigned argsLength) override;
};