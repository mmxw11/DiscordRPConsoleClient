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
    //TODO: split args
    return false;
}