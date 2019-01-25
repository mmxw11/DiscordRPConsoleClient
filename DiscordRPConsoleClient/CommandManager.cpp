#include "pch.h"

#include "CommandManager.h"
#include "StringUtils.h"
#include "ExitCommand.h"
#include "HelpCommand.h"
#include "ReInitDiscordCommand.h"
#include "ClearPresenceCommand.h"
#include "StateCommand.h"
#include "DetailsCommand.h"
#include "TimeCommand.h"
#include "ImageCommand.h"
#include "PartySizeCommand.h"
#include "GameJoinInfoCommand.h"
#include "SpectateInfoCommand.h"

void CommandManager::registerCommand(std::unique_ptr<ICommand> command) {
    commandNames.emplace_back(command->getCommandName());
    commands.emplace(command->getCommandName(), std::move(command));
}

void CommandManager::registerCommands() {
    // Common commands.
    registerCommand(std::make_unique<ExitCommand>());
    registerCommand(std::make_unique<HelpCommand>());
    // Discord specific commands.
    registerCommand(std::make_unique<ReInitDiscordCommand>());
    registerCommand(std::make_unique<ClearPresenceCommand>());
    registerCommand(std::make_unique<StateCommand>());
    registerCommand(std::make_unique<DetailsCommand>());
    registerCommand(std::make_unique<TimeCommand>());
    registerCommand(std::make_unique<ImageCommand>());
    registerCommand(std::make_unique<PartySizeCommand>());
    registerCommand(std::make_unique<GameJoinInfoCommand>());
    registerCommand(std::make_unique<SpectateInfoCommand>());
}

bool CommandManager::dispatchCommand(std::string& commandLineInput) {
    std::vector<std::string> cmdInfoStorage;
    sutils::parseCommandLineArgs(commandLineInput, cmdInfoStorage);
    // Remove args from commandLineInput and leave only the command name, first element is always the command.
    commandLineInput = cmdInfoStorage.front();
    sutils::toUpperCase(commandLineInput);
    std::unordered_map<std::string, std::unique_ptr<ICommand>>::const_iterator it = commands.find(commandLineInput);
    if (it == commands.end()) {
        // Command not found.
        return false;
    }
    const std::unique_ptr<ICommand>& icommand = it->second;
    unsigned requiredArgCount = static_cast<unsigned>(icommand->getRequiredArgumentsCount());
    if (cmdInfoStorage.size() - 1 < requiredArgCount) {
        std::cout << commandLineInput << ": Missing parameters." << std::endl;
        std::cout << "Usage: " << icommand->getUsage() << std::endl;
        return true;
    }
    // Subtract one because the first element is always the command name.
    unsigned argsLength = static_cast<unsigned>(cmdInfoStorage.size()) - 1;
    std::string* args = nullptr;
    if (argsLength != 0) {
        // Advance the pointer address, args start at the second array element.
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

const std::vector<std::string>& CommandManager::getCommandNames() const {
    return commandNames;
}