#pragma once

#include <string>

struct PresenceSettings {

    std::string state;
    std::string details;
    int64_t startTimestamp;
    int64_t endTimestamp;
    std::string largeImageKey;
    std::string largeImageText;
    std::string smallImageKey;
    std::string smallImageText;
    int partySize;
    int partyMax;
    bool displaySpectateInfo;

    void clearAll() {
        state.clear();
        details.clear();
        startTimestamp = 0;
        endTimestamp = 0;
        largeImageKey.clear();
        largeImageText.clear();
        smallImageKey.clear();
        smallImageText.clear();
        partySize = 0;
        partyMax = 0;
        displaySpectateInfo = false;
    }
};