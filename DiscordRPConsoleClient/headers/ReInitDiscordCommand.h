#pragma once

#include "ICommand.h"

class ReInitDiscordCommand : public ICommand {

public:
    ReInitDiscordCommand();
    void executeCommand(std::string* args, unsigned argsLength) override;
};

