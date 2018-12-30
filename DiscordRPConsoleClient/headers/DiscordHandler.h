#pragma once

#include <chrono>
//#include "discord-rpc/discord_rpc.h"

struct DiscordRichPresence;

class DiscordHandler {

public:
    DiscordHandler(const DiscordHandler&) = delete;
    DiscordHandler& operator=(const DiscordHandler&) = delete;
    enum State {
        INITIALIZED,
        CONNECTED,
        UNINITIALIZED
    };
    bool initialize();
    bool uninitialize();
    bool clearPresenceInfo();

    //TODO:
    void setState(const std::string state);
    void setDetails(const std::string details);

    void setStartTimestamp();
    void setEndTimestamp();

    void setLargeImage(const std::string imageName, const std::string imageText = NULL);
    void setSmallImage(const std::string imageName, const std::string imageText = NULL); // CHECK IF LARGE IMAGE SET

    void setPartyInfo(const int partySize, const int partyMax); //TODO CHECK IF STATE SET!

    static DiscordHandler& getInstance();
    bool isCallbackUpdate();
    State getHandlerState() const;
private:
    DiscordHandler();
    ~DiscordHandler();
    //discord event listeners
    static void handleDiscordReady(const struct DiscordUser* connectedUser);
    static void handleDiscordDisconnected(int errcode, const char* message);
    static void handleDiscordError(int errcode, const char* message);
    // variables
    State handlerState;
    static DiscordRichPresence discordPresence;
    std::chrono::steady_clock::time_point lastCallbackUpdate;
};