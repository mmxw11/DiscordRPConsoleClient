#include "pch.h"

#include "SetDetailsCommand.h"
#include "DiscordHandler.h"
#include "StringUtils.h"

SetDetailsCommand::SetDetailsCommand() :
    ICommand("setdetails", "Set what the user is currently doing. (\"Competitive - Captain's Mode\", \"In Queue\", \"Unranked PvP\", \"reset\")") {
    addArgument("details", true);
}

void SetDetailsCommand::executeCommand(std::string* args, unsigned argsLength) {
    std::string& details = args[0];
    sutils::trim(details);
    if (details.empty()) {
        std::cout << "Does an empty string look like good details to you?\nIf you are looking to reset your details use \"setdetails reset\" instead." << std::endl;
        return;
    }
    DiscordHandler& dhandler = DiscordHandler::getInstance();
    bool reset = sutils::equalsIgnoreCase(details, "reset");
    bool updated = dhandler.setDetails(reset ? "" : details, true);
    if (reset) {
        std::cout << "Resetting details." << std::endl;
    } else {
        std::cout << "Updating details to \"" << details << "\"." << std::endl;
    }
    if (!updated) {
        dhandler.printNotConnectedErrorMessage();
    }
}