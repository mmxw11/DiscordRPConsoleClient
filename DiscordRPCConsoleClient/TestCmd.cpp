#include "pch.h"

#include "TestCmd.h"

void TestCmd::executeCommand(unsigned argsCount, std::string* args) {
    std::cout << getCommandName() << " called! argsCount: " << argsCount << std::endl;
    std::cout << "Command Usage: " << getUsage() << std::endl;
    std::cout << "Command description: " << getDescription() << std::endl;
    std::cout << "Command arguments" << std::endl;
    for (const std::pair<const std::string, bool>& entry : getArguments()) {
        std::cout << "key: " << entry.first << '\t' << "value: " << entry.second << std::endl;
    }
    std::cout << "Command call Args:" << std::endl;
    for (int i = 0; i < argsCount; i++) {
        std::string& value = args[i];
        std::cout << value << std::endl;
    }
}