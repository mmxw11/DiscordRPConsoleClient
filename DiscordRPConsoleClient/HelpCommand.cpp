#include "pch.h"

#include "HelpCommand.h"
#include "ApplicationManager.h"
#include "StringUtils.h"

HelpCommand::HelpCommand(ApplicationManager& appManager) :
    ICommand(appManager, "help", "Display help about the commands.") {
    addArgument("command-name", false);
}

void HelpCommand::executeCommand(std::string* args, unsigned argsLength) {
    CommandManager& commandManager = appManager.getCommandManager();
    if (argsLength > 0) {
        std::string& argCommandName = args[0];
        sutils::trim(argCommandName);
        sutils::toUpperCase(argCommandName);
        const ICommand* icommand = commandManager.getCommand(argCommandName);
        if (icommand == nullptr) {
            std::cout << "'" << argCommandName << "' is not a recognized command, \nUse " << getCommandName() << " command to see a list of available commands.\n" << std::endl;
            return;
        }
        std::cout << argCommandName << ": " << icommand->getDescription() << std::endl;
        if (icommand->getArguments().size() > 0) {
            std::cout << "Usage: " << icommand->getUsage() << std::endl;
        }
    } else {
        std::cout << "Use " << getCommandName() << " command-name for more information on a specific command." << std::endl;
        for (auto& entry : commandManager.getCommands()) {
            const std::unique_ptr<ICommand>& icommand = entry.second;
            std::string icommandName = icommand->getCommandName();
            sutils::addPaddingToRight(icommandName, 20);
            std::cout << icommandName << icommand->getDescription() << std::endl;
        }
    }
}