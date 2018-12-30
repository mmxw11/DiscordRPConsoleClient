#include "pch.h"

#include "SetUserStatusCommand.h"
#include "DiscordHandler.h"
#include "StringUtils.h"

SetUserStatusCommand::SetUserStatusCommand() :
    ICommand("setstatus", "Set the user's current status. (\"Looking to Play\", \"Playing Solo\", \"In a Group\", \"reset\")") {
    addArgument("status", true);
}

void SetUserStatusCommand::executeCommand(std::string* args, unsigned argsLength) {
    std::string& status = args[0];
    sutils::trim(status);
    if (status.empty()) {
        std::cout << "Does an empty string look like a good status to you?\nIf you are looking to reset your status use \"setstatus reset\" instead." << std::endl;
        return;
    }
    DiscordHandler& dhandler = DiscordHandler::getInstance();
    bool reset = sutils::equalsIgnoreCase(status, "reset");
    bool connected = dhandler.setStatus(reset ? nullptr : status.c_str());
    if (!connected) {
        dhandler.printNotConnectedErrorMessage();
        return;
    }
    if (reset) {
        std::cout << "Resetting status." << std::endl;
    } else {
        std::cout << "Updating status to \"" << status << "\"." << std::endl;
    }
}