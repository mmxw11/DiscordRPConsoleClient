#include "pch.h"

#include "SetImageCommand.h"
#include "DiscordHandler.h"
#include "StringUtils.h"
#include <set>
#include <unordered_map>

SetImageCommand::SetImageCommand() :
    ICommand("setimage", "Set images for profile artwork + tooltip details. (\"--largeimage/--smallimage --image image_name --tooltip image_info\")") {
    addArgument("--largeimage/--smallimage", true);
    addArgument("--image image_name/reset", false);
    addArgument("--tooltip image_info/reset", false);
}

void SetImageCommand::executeCommand(std::string* args, unsigned argsLength) {
    std::string& type = args[0];
    sutils::trim(type);
    sutils::toLowerCase(type);
    DiscordHandler& dhandler = DiscordHandler::getInstance();
    bool update = parseImageOptions(args, argsLength);
    if (update) {
        if (!dhandler.updatePresence()) {
            dhandler.printNotConnectedErrorMessage();
        }
    }
}

bool SetImageCommand::parseImageOptions(std::string* args, unsigned argsLength) const {
    std::set<std::string> imageTypes;
    std::unordered_map<std::string, std::string*> options;
    const std::string* lastImageType = nullptr;
    const std::string* lastOption = nullptr;
    bool update = false;
    for (unsigned i = 0; i < argsLength; i++) {
        // check for new image type.
        if (sutils::equalsIgnoreCase(args[i], "--largeimage") || sutils::equalsIgnoreCase(args[i], "--smallimage")) {
            // set previous settings.
            if (lastImageType != nullptr) {
                imageTypes.emplace(*lastImageType);
                bool updateRequired = setImageOptions(*lastImageType, options);
                if (!update && updateRequired) {
                    update = true;
                }
            }
            // detected a new image type.
            sutils::toLowerCase(args[i]);
            lastImageType = &args[i];
            // reset previous values.
            options.clear();
            lastOption = nullptr;
            continue;
        }
        // check if image type is already set or null.
        if (lastImageType == nullptr) {
            std::cout << "Ignored an option \"" << args[i] << "\" because image type is not set! Use: --largeimage or --smallimage!" << std::endl;
            continue;
        } else if (imageTypes.find(*lastImageType) != imageTypes.end()) {
            // image type is already set.
            if (!args[i].rfind("--", 0)) {
                std::cout << "Ignored an option \"" << args[i] << "\" because the image type \"" << *lastImageType << "\" is already set!" << std::endl;
            }
            continue;
        }
        //check options.
        if (lastOption == nullptr) {
            if (args[i].rfind("--", 0)) {
                // found value but no option specifier.
                std::cout << "Ignored the value \"" << args[i] << "\" because no option was set for it!" << std::endl;
            } else {
                // new setting option.
                sutils::toLowerCase(args[i]);
                if (options.find(args[i]) != options.end()) {
                    // already set
                    std::cout << "Ignored an option \"" << args[i] << "\" because options for the image type of \"" << *lastImageType << "\" are already set!" << std::endl;
                } else {
                    lastOption = &args[i];
                }
            }
            continue;
        }
        // get the value.
        options.emplace(*lastOption, &args[i]);
        lastOption = nullptr;
    }
    // update last image if needed.
    if (lastImageType != nullptr) {
        bool updateRequired = setImageOptions(*lastImageType, options);
        if (!update && updateRequired) {
            update = true;
        }
    }
    return update;
}

bool SetImageCommand::setImageOptions(const std::string& imageType, const std::unordered_map<std::string, std::string*>& options) const {
    const bool large = imageType == "--largeimage";
    const std::string message = "\"" + std::string(large ? "Large" : "Small").append(" image\"");
    DiscordHandler& dhandler = DiscordHandler::getInstance();
    bool update = false;
    // image.
    std::string data = "--image";
    if (shouldUpdateImageData(data, options)) {
        update = dhandler.setImage(data, large);
        sendUpdateFeedback(message, data.empty());
    }
    // image tooltip.
    data = "--tooltip";
    if (shouldUpdateImageData(data, options)) {
        update = dhandler.setImageText(data, large);
        bool reset = data.empty();
        sendUpdateFeedback(message + " tooltip" + (reset ? "" : " to \"" + data + "\""), reset);
    }
    if (!update) {
        std::cout << message << ": nothing to update." << std::endl;
    }
    return update;
}

bool SetImageCommand::shouldUpdateImageData(std::string& data, const std::unordered_map<std::string, std::string*>& options) const {
    auto key = options.find(data);
    if (key == options.end()) {
        // key not found.
        return false;
    }
    const std::string& value = *key->second;
    if (value.empty()) {
        return false;
    }
    bool reset = sutils::equalsIgnoreCase(value, "reset");
    data = reset ? "" : value;
    return true;
}

void SetImageCommand::sendUpdateFeedback(const std::string& str, bool reset) const {
    if (reset) {
        std::cout << "Resetting " << str << "." << std::endl;
    } else {
        std::cout << "Updating " << str << "." << std::endl;
    }
}