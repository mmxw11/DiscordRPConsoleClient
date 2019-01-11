#include "pch.h"

#include "SpectateInfoCommand.h"
#include "DiscordHandler.h"
#include "StringUtils.h"

void SpectateInfoCommand::executeCommand(std::string* args, unsigned argsLength) {
    const std::string& visibility = args[0];
    if (!sutils::equalsIgnoreCase("show", visibility) && !sutils::equalsIgnoreCase("hide", visibility)) {
        std::cout << "Not a valid visibility setting! Use \"show\" or \"hide\"." << std::endl;
        return;
    }
    DiscordHandler& dhandler = DiscordHandler::getInstance();
    bool show = sutils::equalsIgnoreCase(visibility, "show");
    bool updated = dhandler.setSpectateInfo(show, true);
    std::cout << "Setting spectate visibility to \"" << (show ? "show" : "hide") << "\"." << std::endl;
    if (!updated) {
        dhandler.printNotConnectedErrorMessage();
    }
}