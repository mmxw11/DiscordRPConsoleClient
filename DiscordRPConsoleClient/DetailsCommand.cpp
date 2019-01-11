#include "pch.h"

#include "DetailsCommand.h"
#include "DiscordHandler.h"
#include "StringUtils.h"

void DetailsCommand::executeCommand(std::string* args, unsigned argsLength) {
    std::string& details = args[0];
    sutils::trim(details);
    if (details.empty()) {
        std::cout << "Details cannot be empty!\nIf you are looking to reset your details use \"details reset\" instead." << std::endl;
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