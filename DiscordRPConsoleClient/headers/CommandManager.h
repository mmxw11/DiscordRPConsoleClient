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
    void registerCommand(std::unique_ptr<ICommand> command);
    void registerCommands();
    bool dispatchCommand(std::string& commandLineInput);
    const ICommand* getCommand(const std::string& commandName);
    const std::unordered_map<std::string, std::unique_ptr<ICommand>>& getCommands() const;
private:
    ApplicationManager& appManager;
    std::unordered_map<std::string, std::unique_ptr<ICommand>> commands;
};