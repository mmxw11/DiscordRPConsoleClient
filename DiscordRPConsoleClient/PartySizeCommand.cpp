#include "pch.h"

#include "PartySizeCommand.h"
#include "DiscordHandler.h"
#include "StringUtils.h"

PartySizeCommand::PartySizeCommand() :
    ICommand("partysize", "Set the user's party size. (\"10 of 10\", \"5 of 8\")") {
    addArgument("set/reset", true);
    addArgument("partySize", false);
    addArgument("partyMax", false);
}

void PartySizeCommand::executeCommand(std::string* args, unsigned argsLength) {
    const std::string& action = args[0];
    bool reset = sutils::equalsIgnoreCase(action, "reset");
    if (!reset && !sutils::equalsIgnoreCase(action, "set")) {
        std::cout << "Unknown action type!" << std::endl;
        return;
    }
    DiscordHandler& dhandler = DiscordHandler::getInstance();
    bool updated;
    if (reset) {
        updated = dhandler.setPartySize(-1, -1, true);
        std::cout << "Resetting party size." << std::endl;
    } else {
        if (argsLength < 3) {
            std::cout << "Missing partySize and partyMax arguments!" << std::endl;
            return;
        }
        int partySize;
        if (!sutils::str2Int(partySize, args[1].c_str())) {
            std::cout << "Does \"" << args[1] << "\" look like an integer to you?" << std::endl;
            return;
        }
        int maxPlayers;
        if (!sutils::str2Int(maxPlayers, args[2].c_str())) {
            std::cout << "Does \"" << args[2] << "\" look like an integer to you?" << std::endl;
            return;
        }
        if (partySize <= 0 || maxPlayers <= 0) {
            std::cout << "Party size and max players must be greater than 0!" << std::endl;
            return;
        }
        std::cout << "Updatig party players to (" << partySize << " of " << maxPlayers << ")" << std::endl;
        updated = dhandler.setPartySize(partySize, maxPlayers, true);
    }
    if (!updated) {
        dhandler.printNotConnectedErrorMessage();
    }
}