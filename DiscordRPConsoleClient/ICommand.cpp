#include "pch.h"

#include "ICommand.h"
#include "StringUtils.h"
#include <algorithm>

ICommand::ICommand(std::string name, std::string description) :
    ICommand(nullptr, name, description) {
}

ICommand::ICommand(ApplicationManager* appManager, std::string name, std::string description) :
    appManager(appManager),
    name(name),
    description(description) {
    sutils::toUpperCase(this->name);
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

int ICommand::getRequiredArgumentsCount() const {
    int count = static_cast<int>(std::count_if(arguments.begin(), arguments.end(), [](auto& entry) {
        return entry.second;
    }));
    return count;
}

const std::unordered_map<std::string, bool>& ICommand::getArguments() const {
    return arguments;
}