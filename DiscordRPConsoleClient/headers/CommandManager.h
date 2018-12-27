#pragma once

#include <string>
#include <unordered_map>
#include <memory>
#include "ICommand.h"

class ApplicationManager; // forward declaration

class CommandManager {

public:
    CommandManager(ApplicationManager& appManager);
    CommandManager(const CommandManager&) = delete;
    CommandManager& operator=(const CommandManager&) = delete;
    bool dispatchCommand(std::string& commandInput);
private:
    ApplicationManager& appManager;
    std::unordered_map<std::string, std::unique_ptr<ICommand>> commands;
};