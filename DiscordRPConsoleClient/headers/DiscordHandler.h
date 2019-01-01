#pragma once

#include <chrono>
#include <atomic>
#include "PresenceSettings.h"

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
    bool updatePresence();
    bool clearPresenceInfo();
    bool setState(const std::string state, bool update);
    bool setDetails(const std::string details, bool update);
    bool setImage(const std::string image, bool large, bool update);
    bool setImageText(const std::string text, bool large, bool update);

    //TODO:
    void setStartTimestamp();
    void setEndTimestamp();
    void setPartyInfo(const int partySize, const int partyMax); //TODO CHECK IF STATE SET!

    void printNotConnectedErrorMessage() const;

    static DiscordHandler& getInstance();
    bool isCallbackUpdate();
    const std::atomic<State>& getHandlerState() const;
private:
    DiscordHandler();
    ~DiscordHandler();
    //discord event listeners
    static void handleDiscordReady(const struct DiscordUser* connectedUser);
    static void handleDiscordDisconnected(int errcode, const char* message);
    static void handleDiscordError(int errcode, const char* message);
    // variables
    std::atomic<State> handlerState;
    PresenceSettings presenceSettings;
    std::chrono::steady_clock::time_point lastCallbackUpdate;
};