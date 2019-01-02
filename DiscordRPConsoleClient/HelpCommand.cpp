#include "pch.h"

#include "HelpCommand.h"
#include "ApplicationManager.h"
#include "StringUtils.h"

void HelpCommand::executeCommand(std::string* args, unsigned argsLength) {
    CommandManager& commandManager = appManager->getCommandManager();
    if (argsLength > 0) {
        std::string& argCommandName = args[0];
        sutils::trim(argCommandName);
        sutils::toUpperCase(argCommandName);
        const ICommand* icommand = commandManager.getCommand(argCommandName);
        if (icommand == nullptr) {
            std::cout << "'" << argCommandName << "' is not a recognized command, \nUse \"" << getCommandName() << "\" command to see a list of available commands.\n" << std::endl;
            return;
        }
        std::cout << argCommandName << ": " << icommand->getDescription() << std::endl;
        if (icommand->getArguments().size() > 0) {
            std::cout << "Usage: " << icommand->getUsage() << std::endl;
        }
    } else {
        std::cout << "Use \"" << getCommandName() << " command-name\" for more information on a specific command." << std::endl;
        for (std::string commandName : commandManager.getCommandNames()) { // don't take as reference so we can add padding to it. 
            const std::string& description = commandManager.getCommand(commandName)->getDescription();
            sutils::addPaddingToRight(commandName, 20);
            std::cout << commandName << description << std::endl;
        }
    }
}