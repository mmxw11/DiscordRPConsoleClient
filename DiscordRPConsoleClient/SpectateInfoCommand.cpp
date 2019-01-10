#include "pch.h"

#include "SpectateInfoCommand.h"
#include "DiscordHandler.h"
#include "StringUtils.h"

void SpectateInfoCommand::executeCommand(std::string* args, unsigned argsLength) {
    std::string& visibility = args[0];
    if (visibility.empty()) {
        std::cout << "Does an empty string look like a visibility settings to you?\nUse \"show\" or \"hide\"." << std::endl;
        return;
    }
    DiscordHandler& dhandler = DiscordHandler::getInstance();
    bool show = sutils::equalsIgnoreCase(visibility, "show");
    bool updated = dhandler.setSpectateInfo(show, true);
    if (show) {
        std::cout << "Spectate visibility set to show." << std::endl;
    } else {
        std::cout << "Spectate visibility set to hide." << std::endl;
    }
    if (!updated) {
        dhandler.printNotConnectedErrorMessage();
    }
}