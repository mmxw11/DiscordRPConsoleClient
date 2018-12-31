#pragma once

#include <chrono>
#include <atomic>
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
    bool setStatus(const char* status);

    //TODO:
    void setDetails(const std::string details);

    void setStartTimestamp();
    void setEndTimestamp();

    void setLargeImage(const std::string imageName, const std::string imageText);
    void setSmallImage(const std::string imageName, const std::string imageText); // CHECK IF LARGE IMAGE SET

    void setPartyInfo(const int partySize, const int partyMax); //TODO CHECK IF STATE SET!

    void printNotConnectedErrorMessage() const;

    static DiscordHandler& getInstance();
    bool isCallbackUpdate();
    const std::atomic<State>& getHandlerState() const;
private:
    DiscordHandler();
    ~DiscordHandler();
    bool updatePresence();
    //discord event listeners
    static void handleDiscordReady(const struct DiscordUser* connectedUser);
    static void handleDiscordDisconnected(int errcode, const char* message);
    static void handleDiscordError(int errcode, const char* message);
    // variables
    std::atomic<State> handlerState;
    static DiscordRichPresence discordPresence;
    std::chrono::steady_clock::time_point lastCallbackUpdate;
};