#pragma once

#include "ICommand.h"

class ReInitDiscordCommand : public ICommand {

public:
    ReInitDiscordCommand() :
        ICommand("reinitdiscord", "Reinitialize Discord.") {
    }
    void executeCommand(std::string* args, unsigned argsLength) override;
};