#pragma once

#include "ICommand.h"

class GameJoinInfoCommand : public ICommand {

public:
    GameJoinInfoCommand() :
        ICommand("gamejoininfo", "Display a join button on your profile, and enable sending join invites (to Discord chat channels) that won't do anything. The ID you specify is tied to the invites you send. As it changes, the invite(s) expire.") {
        addArgument("show/hide", true);
        addArgument("partyId", false);
    }
    void executeCommand(std::string* args, unsigned argsLength) override;
};