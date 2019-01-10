#pragma once

#include "ICommand.h"

class SpectateInfoCommand : public ICommand {

public:
    SpectateInfoCommand() :
        ICommand("spectateinfo", "Display a dummy spectate button on your profile, and enable sending spectate invites (to Discord chat channels) that won't do anything.") {
        addArgument("show/hide", true);
    }
    void executeCommand(std::string* args, unsigned argsLength) override;
};