#pragma once

#include "ICommand.h"
#include <unordered_map>

class ImageCommand : public ICommand {

public:
    ImageCommand() :
        ICommand("image", "Set images for profile artwork + image tooltip details. (\"image name > sample_image tooltip > This is displayed when you however\")") {
        addArgument("--largeimage/--smallimage", true);
        addArgument("--image", false);
        addArgument("image_name", false);
        addArgument("--tooltip", false);
        addArgument("image_tooltip", false);
        addArgument("reset", false);
    }
    void executeCommand(std::string* args, unsigned argsLength) override;
private:
    bool parseImageOptions(std::string* args, unsigned argsLength) const;
    bool setImageOptions(const std::string& imageType, const std::unordered_map<std::string, std::string*>& options) const;
    bool shouldUpdateImageData(std::string& data, const std::unordered_map<std::string, std::string*>& options) const;
    void sendUpdateFeedback(const std::string& str, const bool& reset) const;
};