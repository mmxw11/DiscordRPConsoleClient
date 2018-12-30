#pragma once

#include "ICommand.h"

class ReInitDiscordCommand : public ICommand {

public:
    ReInitDiscordCommand(ApplicationManager& appManager);
    void executeCommand(std::string* args, unsigned argsLength) override;
};

