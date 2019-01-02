#pragma once

#include "ICommand.h"

class TimeCommand : public ICommand {

public:
    TimeCommand();
    void executeCommand(std::string* args, unsigned argsLength) override;
private:
    bool updateTime(const std::string& type, const std::string& timeStr);
};