#pragma once

#include "ICommand.h"

class SpectateInfoCommand : public ICommand {

public:
    SpectateInfoCommand() :
        ICommand("spectateinfo", "Display a dummy spectate button on your profile, and send spectate invites that won't do anything.") {
        addArgument("show/hide", true);
    }
    void executeCommand(std::string* args, unsigned argsLength) override;
};