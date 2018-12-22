#include "pch.h"

#include "ICommand.h"

ICommand::ICommand(ApplicationManager& appManager, std::string name, std::string description) :
    appManager(appManager),
    name(name),
    description(description) {
}

void ICommand::addArgument(std::string arg, bool required) {
    arguments.emplace(arg, required);
}

const std::string& ICommand::getCommandName() const {
    return name;
}

std::string ICommand::getUsage() const {
    std::string usage = name;
    for (auto& entry : arguments) {
        usage += " " + (entry.second ? "<" + entry.first + ">" : "[" + entry.first + "]");
    }
    return usage;
}

const std::string& ICommand::getDescription() const {
    return description;
}

const std::unordered_map<std::string, bool>& ICommand::getArguments() const {
    return arguments;
}