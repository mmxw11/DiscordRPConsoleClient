#include "pch.h"

#include "CommandManager.h"
#include "ApplicationManager.h"
#include "StringUtils.h"

CommandManager::CommandManager(ApplicationManager& appManager) :
    appManager(appManager) {
}

bool CommandManager::dispatchCommand(std::string& commandInput) {
    if (sutils::equalsIgnoreCase(commandInput, "exit")) {
        // this is only temporarily.
        appManager.shutdown();
        return true;
    }
    std::cout << "Command args:" << std::endl;
    std::vector<std::string> argsStorage;
    sutils::parseCommandLineArgs(commandInput, argsStorage);

    std::string* args = argsStorage.data();
    for (size_t i = 0; i < argsStorage.size(); i++) {
        std::cout << i << ". " << args[i] << std::endl;
    }
    //TODO
    return false;
}