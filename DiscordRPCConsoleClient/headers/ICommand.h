#pragma once

#include <string>
#include <unordered_map>

class ApplicationManager;

class ICommand {

public:
    ICommand(ApplicationManager& appManager, std::string name, std::string description);
    virtual ~ICommand() = default;

    virtual void executeCommand(std::string* args, unsigned argsLength) = 0;
    const std::string& getCommandName() const;
    const std::string& getDescription() const;
    std::string getUsage() const;
    const std::unordered_map<std::string, bool>& getArguments() const;
protected:
    ApplicationManager& appManager;
    void addArgument(std::string arg, bool required);
private:
    std::string name;
    std::string description;
    std::unordered_map<std::string, bool> arguments;
};