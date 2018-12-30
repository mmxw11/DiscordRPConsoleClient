#include "pch.h"

#include "ReInitDiscordCommand.h"
#include "DiscordHandler.h"

ReInitDiscordCommand::ReInitDiscordCommand(ApplicationManager& appManager) :
    ICommand(appManager, "reinitdiscord", "Reinitialize Discord.") {
}

void ReInitDiscordCommand::executeCommand(std::string* args, unsigned argsLength) {
    DiscordHandler& dhandler = DiscordHandler::getInstance();
    if (dhandler.uninitialize()) {
        std::cout << "Uninitialized discord." << std::endl;
    }
    if (!dhandler.initialize()) {
        std::cout << "[ERROR] Tried to initialize Discord when it's already initialized!" << std::endl;
    }
}