#include "pch.h"

#include "StateCommand.h"
#include "DiscordHandler.h"
#include "StringUtils.h"

void StateCommand::executeCommand(std::string* args, unsigned argsLength) {
    std::string& state = args[0];
    sutils::trim(state);
    if (state.empty()) {
        std::cout << "Does an empty string look like a good state to you?\nIf you are looking to reset your party state use \"state reset\" instead." << std::endl;
        return;
    }
    DiscordHandler& dhandler = DiscordHandler::getInstance();
    bool reset = sutils::equalsIgnoreCase(state, "reset");
    bool updated = dhandler.setState(reset ? "" : state, true);
    if (reset) {
        std::cout << "Resetting party state." << std::endl;
    } else {
        std::cout << "Updating party state to \"" << state << "\"." << std::endl;
    }
    if (!updated) {
        dhandler.printNotConnectedErrorMessage();
    }
}