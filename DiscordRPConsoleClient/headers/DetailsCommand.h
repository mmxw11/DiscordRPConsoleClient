#pragma once

#include "ICommand.h"

class DetailsCommand : public ICommand {

public:
    DetailsCommand() :
        ICommand("details", "Set what the user is currently doing. (\"Competitive - Captain's Mode\", \"In Queue\", \"Unranked PvP\")") {
        addArgument("details/reset", true);
    }
    void executeCommand(std::string* args, unsigned argsLength) override;
};