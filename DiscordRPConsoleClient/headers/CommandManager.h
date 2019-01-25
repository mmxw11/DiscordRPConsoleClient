#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include "ICommand.h"

class CommandManager {

public:
    CommandManager() = default;
    CommandManager(const CommandManager&) = delete;
    CommandManager& operator=(const CommandManager&) = delete;
    void registerCommand(std::unique_ptr<ICommand> command);
    void registerCommands();
    bool dispatchCommand(std::string& commandLineInput);
    const ICommand* getCommand(const std::string& commandName);
    const std::vector<std::string>& getCommandNames() const;
private:
    std::vector<std::string> commandNames;
    std::unordered_map<std::string, std::unique_ptr<ICommand>> commands;
};