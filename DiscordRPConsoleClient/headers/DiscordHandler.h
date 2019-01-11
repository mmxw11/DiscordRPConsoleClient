#pragma once

#include <chrono>
#include <atomic>
#include "PresenceSettings.h"

class DiscordHandler {

public:
    DiscordHandler(const DiscordHandler&) = delete;
    DiscordHandler& operator=(const DiscordHandler&) = delete;
    enum class State {
        INITIALIZED,
        CONNECTED,
        UNINITIALIZED
    };
    void setApplicationId(const std::string& applicationId);
    bool initialize();
    bool uninitialize();
    bool updatePresence();
    bool clearPresenceInfo();
    bool setState(const std::string& state, bool update);
    bool setDetails(const std::string& details, bool update);
    bool setImage(const std::string& image, bool large, bool update);
    bool setImageText(const std::string& text, bool large, bool update);
    bool setPartySize(const int partySize, const int partyMax, bool update);
    bool setStartTimestamp(const int64_t timestamp, bool update);
    bool setEndTimestamp(const int64_t timestamp, bool update);
    bool setGameJoinInfo(const std::string& id, bool update);
    bool setSpectateInfo(const bool show, bool update);
    void printNotConnectedErrorMessage() const;
    static DiscordHandler& getInstance();
    bool isCallbackUpdate();
    const std::atomic<State>& getHandlerState() const;
private:
    DiscordHandler();
    ~DiscordHandler();
    // Discord event handlers
    static void handleDiscordReady(const struct DiscordUser* connectedUser);
    static void handleDiscordDisconnected(int errcode, const char* message);
    static void handleDiscordError(int errcode, const char* message);
    static void handleDiscordJoin(const char* secret);
    static void handleDiscordSpectate(const char* secret);
    static void handleDiscordJoinRequest(const struct DiscordUser* request);
    // variables
    std::string applicationId;
    std::atomic<State> handlerState;
    PresenceSettings presenceSettings;
    std::chrono::steady_clock::time_point lastCallbackUpdate;
};