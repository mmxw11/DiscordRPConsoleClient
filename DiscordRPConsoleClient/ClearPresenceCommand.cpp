#include "pch.h"

#include "ClearPresenceCommand.h"
#include "DiscordHandler.h"

ClearPresenceCommand::ClearPresenceCommand() :
    ICommand("clearpresence", "Clear presence information.") {
}

void ClearPresenceCommand::executeCommand(std::string* args, unsigned argsLength) {
    DiscordHandler& dhandler = DiscordHandler::getInstance();
    bool updated = dhandler.clearPresenceInfo();
    std::cout << "Clearing presence information." << std::endl;
    if (!updated) {
        dhandler.printNotConnectedErrorMessage();
    }
}