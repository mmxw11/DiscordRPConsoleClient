#include "pch.h"

#include "SetStateCommand.h"
#include "DiscordHandler.h"
#include "StringUtils.h"

SetStateCommand::SetStateCommand() :
    ICommand("setstate", "Set the user's current status. (\"Looking to Play\", \"Playing Solo\", \"In a Group\", \"reset\")") {
    addArgument("state", true);
}

void SetStateCommand::executeCommand(std::string* args, unsigned argsLength) {
    std::string& state = args[0];
    sutils::trim(state);
    if (state.empty()) {
        std::cout << "Does an empty string look like a good state to you?\nIf you are looking to reset your status use \"setstatus reset\" instead." << std::endl;
        return;
    }
    DiscordHandler& dhandler = DiscordHandler::getInstance();
    bool reset = sutils::equalsIgnoreCase(state, "reset");
    bool updated = dhandler.setState(reset ? "" : state, true);
    if (reset) {
        std::cout << "Resetting state." << std::endl;
    } else {
        std::cout << "Updating state to \"" << state << "\"." << std::endl;
    }
    if (!updated) {
        dhandler.printNotConnectedErrorMessage();
    }
}