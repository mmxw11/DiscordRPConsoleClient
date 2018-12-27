#include "pch.h"

#include "CommandManager.h"
#include "StringUtils.h"
#include "TestCmd.h"
#include "ExitCommand.h"
#include "HelpCommand.h"

CommandManager::CommandManager(ApplicationManager& appManager) :
    appManager(appManager) {
    registerCommand(std::make_unique<TestCmd>(appManager, "test_test_test"));
    registerCommand(std::make_unique<ExitCommand>(appManager));
    registerCommand(std::make_unique<HelpCommand>(appManager));
}

void CommandManager::registerCommand(std::unique_ptr<ICommand> command) {
    commands.emplace(command->getCommandName(), std::move(command));
}

bool CommandManager::dispatchCommand(std::string& commandLineInput) {
    /**if (sutils::equalsIgnoreCase(commandInput, "exit")) {
        // this is only temporarily.
        appManager.shutdown();
        return true;
    }*/
    std::vector<std::string> cmdInfoStorage;
    sutils::parseCommandLineArgs(commandLineInput, cmdInfoStorage);
    // remove args from commandLineInput and leave only the command name, first element is always the command.
    commandLineInput = cmdInfoStorage.front();
    sutils::toUpperCase(commandLineInput);
    std::unordered_map<std::string, std::unique_ptr<ICommand>>::const_iterator it = commands.find(commandLineInput);
    if (it == commands.end()) {
        // command not found.
        return false;
    }
    const std::unique_ptr<ICommand>& icommand = it->second;
    unsigned requiredArgCount = icommand->getRequiredArgumentsCount();
    if (cmdInfoStorage.size() - 1 < requiredArgCount) {
        std::cout << commandLineInput << ": Missing parameters." << std::endl;
        std::cout << "Usage: " << icommand->getUsage() << std::endl;
        return true;
    }
    // subtract one because the first element is always the command name.
    unsigned argsLength = cmdInfoStorage.size() - 1;
    std::string* args = nullptr;
    if (argsLength != 0) {
        // advance the pointer address, args start at the second array element.
        args = cmdInfoStorage.data() + 1;
    }
    icommand->executeCommand(args, argsLength);
    return true;
}

const ICommand* CommandManager::getCommand(const std::string& commandName) {
    std::unordered_map<std::string, std::unique_ptr<ICommand>>::const_iterator it = commands.find(commandName);
    if (it == commands.end()) {
        return nullptr;
    }
    return it->second.get();
}

const std::unordered_map<std::string, std::unique_ptr<ICommand>>& CommandManager::getCommands() const {
    return commands;
}
