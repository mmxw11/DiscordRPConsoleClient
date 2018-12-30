#include "pch.h"

#include "DiscordHandler.h"
#include "discord-rpc/discord_rpc.h"

// link discord library
#if defined(_WIN64)
#pragma comment(lib, "discord-rpc-win64.lib")
#else
#pragma comment(lib, "discord-rpc-win32.lib")
#endif

DiscordHandler::DiscordHandler() :
    handlerState(State::UNINITIALIZED) {
}

DiscordHandler::~DiscordHandler() {
    uninitialize();
}
//TODO: REMOVE
//std::cout << "Tried to uninitialize handler when it's alreay uninitialized!" << std::endl;
 //assert((this->handlerState == State::UNINITIALIZED  && "Tried to initialize handler it's already initialized!"));
static void UpdatePresence() { // TEST CODE
    DiscordRichPresence discordPresence;
    memset(&discordPresence, 0, sizeof(discordPresence));
    discordPresence.state = "Playing TEst";
    discordPresence.details = "Test";
    discordPresence.startTimestamp = 1546180244159;
    discordPresence.endTimestamp = 1546180844159;
    discordPresence.largeImageText = "Numbani";
    discordPresence.smallImageText = "Rogue - Level 99999";
    Discord_UpdatePresence(&discordPresence);
}

bool DiscordHandler::initialize(const std::string& applicationId) {
    if (handlerState != State::UNINITIALIZED) {
        return false;
    }
    DiscordEventHandlers handlers;
    memset(&handlers, 0, sizeof(handlers));
    handlers.ready = handleDiscordReady;
    handlers.disconnected = handleDiscordDisconnected;
    handlers.errored = handleDiscordError;

    Discord_Initialize(applicationId.c_str(), &handlers, 1, NULL);
    std::cout << "Waiting for Discord connection (Ctrl + C to terminate)..." << std::endl;
    this->handlerState = State::INITIALIZED;
    return true;
}

bool DiscordHandler::uninitialize() {
    if (handlerState == State::UNINITIALIZED) {
        return false;
    }
    Discord_Shutdown();
    this->handlerState = State::UNINITIALIZED;
    return true;
}

DiscordHandler& DiscordHandler::getInstance() {
    static DiscordHandler instance;
    return instance;
}

bool DiscordHandler::isCallbackUpdate() {
    auto time = std::chrono::steady_clock::now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(time - lastCallbackUpdate);
    if (elapsedTime >= std::chrono::milliseconds(1000)) {
        lastCallbackUpdate = time;
        return true;
    }
    return false;
}

DiscordHandler::State DiscordHandler::getHandlerState() const {
    return handlerState;
}

void DiscordHandler::handleDiscordReady(const DiscordUser* connectedUser) {
    printf("\nDiscord: connected to user %s#%s - %s\n", connectedUser->username, connectedUser->discriminator, connectedUser->userId);
    getInstance().handlerState = State::CONNECTED;
    UpdatePresence(); // TODO: TEST CODE
}

void DiscordHandler::handleDiscordDisconnected(int errcode, const char* message) {
    printf("\nDiscord: disconnected (%d: %s)\n", errcode, message);
    getInstance().uninitialize();
}

void DiscordHandler::handleDiscordError(int errcode, const char* message) {
    printf("\nDiscord: error (%d: %s)\n", errcode, message);
    getInstance().uninitialize();
}
