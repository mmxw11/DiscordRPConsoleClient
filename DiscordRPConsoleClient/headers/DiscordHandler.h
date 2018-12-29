#pragma once

class DiscordHandler {

public:
    DiscordHandler();
    DiscordHandler(const DiscordHandler&) = delete;
    DiscordHandler& operator=(const DiscordHandler&) = delete;
    ~DiscordHandler();
    void init();
    void shutdown();
private:
    bool initialized;
};