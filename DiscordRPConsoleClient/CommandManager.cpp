#include "pch.h"

#include "CommandManager.h"
#include "ApplicationManager.h"
#include "StringUtils.h"
#include "TestCmd.h"

CommandManager::CommandManager(ApplicationManager& appManager) :
    appManager(appManager) {
    commands.emplace("test", std::make_unique<TestCmd>(appManager, "test"));
}

bool CommandManager::dispatchCommand(std::string& commandInput) {
    if (sutils::equalsIgnoreCase(commandInput, "exit")) {
        // this is only temporarily.
        appManager.shutdown();
        return true;
    }
    std::vector<std::string> cmdInfoStorage;
    sutils::parseCommandLineArgs(commandInput, cmdInfoStorage);

    // remove args from commandInput and leave only the command name, first element is always the command.
    commandInput = cmdInfoStorage.front();
    sutils::toLowerCase(commandInput);
    std::unordered_map<std::string, std::unique_ptr<ICommand>>::iterator it = commands.find(commandInput);
    if (it == commands.end()) {
        // command not found.
        return false;
    }
    std::unique_ptr<ICommand>& icommand = it->second;
    int requiredArgCount = icommand->getRequiredArgumentsCount();
    if (cmdInfoStorage.size() - 1 < requiredArgCount) {
        std::cout << "You are missing arguments!" << std::endl;
        //TODO: SHOW USAGE
        return true;
    }
    //TODO: CHECK IF NO ARGS, DONT PASS ANYTHING? CHECK UNSIGNED
    std::string* args = cmdInfoStorage.data() + 1;
    icommand->executeCommand(args, cmdInfoStorage.size() - 1);
    return true;
}