#pragma once

#include "ICommand.h"
#include <unordered_map>

class SetImageCommand : public ICommand {

public:
    SetImageCommand();
    void executeCommand(std::string* args, unsigned argsLength) override;
private:
    bool parseImageOptions(std::string* args, unsigned argsLength) const;
    bool setImageOptions(const std::string& imageType, const std::unordered_map<std::string, std::string*>& options) const;
    bool shouldUpdateImageData(std::string& data, const std::unordered_map<std::string, std::string*>& options) const;
    void sendUpdateFeedback(const std::string& str, const bool& reset) const;
};