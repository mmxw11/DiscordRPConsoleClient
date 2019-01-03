#include "pch.h"

#include "ImageCommand.h"
#include "DiscordHandler.h"
#include "StringUtils.h"
#include <set>

void ImageCommand::executeCommand(std::string* args, unsigned argsLength) {
    DiscordHandler& dhandler = DiscordHandler::getInstance();
    bool updateRequired = parseImageOptions(args, argsLength);
    if (updateRequired) {
        if (!dhandler.updatePresence()) {
            dhandler.printNotConnectedErrorMessage();
        }
    }
}

bool ImageCommand::parseImageOptions(std::string* args, unsigned argsLength) const {
    std::set<std::string> imageTypes;
    std::unordered_map<std::string, std::string*> options;
    const std::string* lastImageType = nullptr;
    const std::string* lastOption = nullptr;
    bool updateRequired = false;
    for (unsigned i = 0; i < argsLength; i++) {
        // Check for new image type.
        if (sutils::equalsIgnoreCase(args[i], "--largeimage") || sutils::equalsIgnoreCase(args[i], "--smallimage")) {
            // Save previous option.
            if (lastImageType) {
                imageTypes.emplace(*lastImageType);
                if (setImageOptions(*lastImageType, options)) {
                    updateRequired = true;
                }
            }
            // Detected a new image type.
            sutils::toLowerCase(args[i]);
            lastImageType = &args[i];
            // Reset previous values.
            options.clear();
            lastOption = nullptr;
            continue;
        }
        // Check if image type is already set or null.
        if (!lastImageType) {
            std::cout << "Ignored an option \"" << args[i] << "\" because image type is not set! Use: --largeimage or --smallimage!" << std::endl;
            continue;
        } else if (imageTypes.find(*lastImageType) != imageTypes.end()) {
            // Image type is already set.
            if (!args[i].rfind("--", 0)) {
                std::cout << "Ignored an option \"" << args[i] << "\" because the image type \"" << *lastImageType << "\" is already set!" << std::endl;
            }
            continue;
        }
        // Check options.
        if (!lastOption) {
            if (args[i].rfind("--", 0)) {
                // Found a value but no option specifier.
                std::cout << "Ignored the value \"" << args[i] << "\" because no option was set for it!" << std::endl;
            } else {
                // New setting option.
                sutils::toLowerCase(args[i]);
                if (options.find(args[i]) != options.end()) {
                    // Already set.
                    std::cout << "Ignored an option \"" << args[i] << "\" because options for the image type of \"" << *lastImageType << "\" are already set!" << std::endl;
                } else {
                    lastOption = &args[i];
                }
            }
            continue;
        }
        // Add the value to the map.
        options.emplace(*lastOption, &args[i]);
        lastOption = nullptr;
    }
    // Update last image if needed.
    if (lastImageType && setImageOptions(*lastImageType, options)) {
        updateRequired = true;
    }
    return updateRequired;
}

bool ImageCommand::setImageOptions(const std::string& imageType, const std::unordered_map<std::string, std::string*>& options) const {
    const bool large = imageType == "--largeimage";
    const std::string message = "\"" + std::string(large ? "Large" : "Small").append(" image\"");
    DiscordHandler& dhandler = DiscordHandler::getInstance();
    bool updateRequired = false;
    // Image.
    std::string data = "--image";
    if (shouldUpdateImageData(data, options)) {
        updateRequired = !dhandler.setImage(data, large, false);
        sendUpdateFeedback(message, data.empty());
    }
    // Image tooltip.
    data = "--tooltip";
    if (shouldUpdateImageData(data, options)) {
        updateRequired = !dhandler.setImageText(data, large, false);
        const bool reset = data.empty();
        sendUpdateFeedback(message + " tooltip" + (reset ? "" : " to \"" + data + "\""), reset);
    }
    if (!updateRequired) {
        std::cout << message << ": nothing to update." << std::endl;
    }
    return updateRequired;
}

bool ImageCommand::shouldUpdateImageData(std::string& data, const std::unordered_map<std::string, std::string*>& options) const {
    auto key = options.find(data);
    if (key == options.end()) {
        // Key not found.
        return false;
    }
    const std::string& value = *key->second;
    if (value.empty()) {
        return false;
    }
    data = sutils::equalsIgnoreCase(value, "reset") ? "" : value;
    return true;
}

void ImageCommand::sendUpdateFeedback(const std::string& str, const bool& reset) const {
    if (reset) {
        std::cout << "Resetting " << str << "." << std::endl;
    } else {
        std::cout << "Updating " << str << "." << std::endl;
    }
}