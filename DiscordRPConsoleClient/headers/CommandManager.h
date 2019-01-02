#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include "ICommand.h"

class ApplicationManager; // forward declaration

class CommandManager {

public:
    CommandManager(ApplicationManager& appManager);
    CommandManager(const CommandManager&) = delete;
    CommandManager& operator=(const CommandManager&) = delete;
    void registerCommand(std::unique_ptr<ICommand> command);
    void registerCommands();
    bool dispatchCommand(std::string& commandLineInput);
    const ICommand* getCommand(const std::string& commandName);
    const std::vector<std::string>& getCommandNames() const;
private:
    ApplicationManager& appManager;
    std::vector<std::string> commandNames;
    std::unordered_map<std::string, std::unique_ptr<ICommand>> commands;
};