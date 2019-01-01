#pragma once

#include <string>

struct PresenceSettings {

    std::string state;
    std::string details;
    std::string largeImageKey;
    std::string largeImageText;
    std::string smallImageKey;
    std::string smallImageText;

    void clearAll() {
        memset(this, 0, sizeof(this));
        state.clear();
        details.clear();
        largeImageKey.clear();
        largeImageText.clear();
        smallImageKey.clear();
        smallImageText.clear();
    }
};