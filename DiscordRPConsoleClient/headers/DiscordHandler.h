#pragma once

class DiscordHandler {

public:
    enum State {
        INITIALIZED,
        CONNECTED,
        UNINITIALIZED
    };
    static DiscordHandler& getInstance();
    bool initialize(const std::string& applicationId);
    bool uninitialize();
    bool isCallbackUpdate();
    State getHandlerState() const;
private:
    DiscordHandler();
    DiscordHandler(const DiscordHandler&) = delete;
    DiscordHandler& operator=(const DiscordHandler&) = delete;
    ~DiscordHandler();
    //discord event listeners
    static void handleDiscordReady(const struct DiscordUser* connectedUser);
    static void handleDiscordDisconnected(int errcode, const char* message);
    static void handleDiscordError(int errcode, const char* message);
    // variables
    State handlerState;
};