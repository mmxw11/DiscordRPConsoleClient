#include "pch.h"

#include "GameJoinInfoCommand.h"
#include "DiscordHandler.h"
#include "StringUtils.h"

void GameJoinInfoCommand::executeCommand(std::string* args, unsigned argsLength) {
    const std::string& visibility = args[0];
    if (!sutils::equalsIgnoreCase("show", visibility) && !sutils::equalsIgnoreCase("hide", visibility)) {
        std::cout << "Not a valid visibility setting! Use \"show\" or \"hide\"." << std::endl;
        return;
    }
    DiscordHandler& dhandler = DiscordHandler::getInstance();
    bool show = sutils::equalsIgnoreCase(visibility, "show");
    bool updated;
    if (show) {
        if (argsLength < 2) {
            std::cout << "You must specify the partyId when setting visibility state to \"show\"." << std::endl;
            std::cout << "The ID you specify is tied to the invites you send. As it changes, the invite(s) expire." << std::endl;
            return;
        }
        const std::string& partyId = args[1];
        if (partyId.empty()) {
            std::cout << "The ID cannot be empty!" << std::endl;
            return;
        }
        updated = dhandler.setGameJoinInfo(partyId, true);
        std::cout << "Setting game join visibility to \"show\" with the partyId of \"" << partyId << "\"." << std::endl;
    } else {
        updated = dhandler.setGameJoinInfo("", true);
        std::cout << "Setting game join visibility to \"hide\"." << std::endl;
    }
    if (!updated) {
        dhandler.printNotConnectedErrorMessage();
    }
}