#include "pch.h"

#include "TestCmd.h"

void TestCmd::executeCommand(std::string* args, unsigned argsLength) {
    std::cout << getCommandName() << " called! argsLength: " << argsLength << std::endl;
    std::cout << "Command Usage: " << getUsage() << std::endl;
    std::cout << "Command description: " << getDescription() << std::endl;
    std::cout << "Command arguments" << std::endl;
    for (const std::pair<const std::string, bool>& entry : getArguments()) {
        std::cout << "key: " << entry.first << '\t' << "value: " << entry.second << std::endl;
    }
    std::cout << "Command call Args:" << std::endl;
    for (unsigned i = 0; i < argsLength; i++) {
        std::string& value = args[i];
        std::cout << value << std::endl;
    }
}