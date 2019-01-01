#pragma once

#include <string>

struct PresenceSettings {

    std::string state;
    std::string details;

    void clearAll() {
        memset(this, 0, sizeof(this));
        state.clear();
        details.clear();
    }
};