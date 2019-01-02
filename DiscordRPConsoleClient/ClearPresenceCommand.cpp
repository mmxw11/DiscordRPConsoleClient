#include "pch.h"

#include "ClearPresenceCommand.h"
#include "DiscordHandler.h"

void ClearPresenceCommand::executeCommand(std::string* args, unsigned argsLength) {
    DiscordHandler& dhandler = DiscordHandler::getInstance();
    bool updated = dhandler.clearPresenceInfo();
    std::cout << "Clearing presence information." << std::endl;
    if (!updated) {
        dhandler.printNotConnectedErrorMessage();
    }
}