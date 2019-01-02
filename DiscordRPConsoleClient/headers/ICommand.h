#pragma once

#include <string>
#include <vector>

class ApplicationManager; // forward declaration

class ICommand {

public:
    ICommand(std::string name, std::string description);
    ICommand(ApplicationManager* appManager, std::string name, std::string description);
    ICommand(const ICommand&) = delete;
    ICommand& operator=(const ICommand&) = delete;
    virtual ~ICommand() = default;
    virtual void executeCommand(std::string* args, unsigned argsLength) = 0;
    const std::string& getCommandName() const;
    const std::string& getDescription() const;
    std::string getUsage() const;
    struct CommandArgument {
        std::string name;
        bool required;
        CommandArgument(std::string name, bool required) : name(name), required(required) {}
    };
    int getRequiredArgumentsCount() const;
    const std::vector<CommandArgument>& getArguments() const;
protected:
    ApplicationManager* appManager;
    void addArgument(std::string arg, bool required);
private:
    std::string name;
    std::string description;
    std::vector<CommandArgument> arguments;
};