#pragma once

#include "ICommand.h"

class TimeCommand : public ICommand {

public:
    TimeCommand() :
        ICommand("time", "Set time displayed on the user's profile. (\"Remaining 10 minutes\", \"Elapsed 30 seconds\")") {
        addArgument("--starttime/--endtime", true);
        addArgument("yyyy-MM-dd HH:mm:ss", false);
        addArgument("reset", false);
    }
    void executeCommand(std::string* args, unsigned argsLength) override;
private:
    bool updateTime(const std::string& type, const std::string& timeStr);
};