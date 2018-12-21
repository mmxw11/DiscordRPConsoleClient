#pragma once

#include <unordered_map>

class ICommand {

public:
    ICommand(std::string name, std::string description);
    virtual ~ICommand() = default;

    virtual void executeCommand(unsigned argsCount, char* args[]) = 0;
    const std::string& getCommandName() const;
    const std::string& getDescription() const;
    std::string getUsage() const;
    const std::unordered_map<std::string, bool>& getArguments() const;
protected:
    void addArgument(std::string arg, bool required);
private:
    std::string name;
    std::string description;
    std::unordered_map<std::string, bool> arguments;
};