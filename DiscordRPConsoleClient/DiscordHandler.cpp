#include "pch.h"

#include "DiscordHandler.h"
#include "discord-rpc/discord_rpc.h"

// link discord library
#if defined(_WIN64)
#pragma comment(lib, "discord-rpc-win64.lib")
#else
#pragma comment(lib, "discord-rpc-win32.lib")
#endif

//DiscordRichPresence DiscordHandler::discordPresence;

DiscordHandler::DiscordHandler() :
    handlerState(State::UNINITIALIZED) {
    // memset(&discordPresence, 0, sizeof(discordPresence));
}

DiscordHandler::~DiscordHandler() {
    uninitialize();
}

/**
TODO:
32-bit build
something is likely leaking memory _CrtDumpMemoryLeaks() -> Detected memory leaks!;
remove app id from init and own function for it (+ ask at startup)
cleaning
-------------------------------------------
disconnect, connect (reinit) command [DONE]
clear presence command [DONE]
const char* state; [DONE]
const char* details; [DONE]

DONT SEND ENDTIMESTAMP WITHOUT STATE OR YOUR DISCORD CRASHES!
int64_t startTimestamp;
int64_t endTimestamp;
ONLY START -> Elpsed
ONLY END -> Remaining
BOTH -> Time left

const char* largeImageKey; [DONE]
const char* largeImageText; [DONE]

----YOU MUST HAVE LARGE IMAGE TO DISPLAY THESE:---
const char* smallImageKey; [DONE]
const char* smallImageText; [DONE]

const char* partyId; [NOT REQUIRED]

----YOU MUST SEND STATE TO DISPLAY THESE:---
MUST BE SENT AT THE SAME TIME!
int partySize, [DONE]
int partyMax; [DONE]

-------------------------------------------

--------------------------------------------------

--------------------------------------------------

 const char* matchSecret; [NOT USED]
const char* joinSecret;   [NOT USED]
const char* spectateSecret; [NOT USED]
int8_t instance; [NOT USED]


*/
//TODO: REMOVE
//std::cout << "Tried to uninitialize handler when it's alreay uninitialized!" << std::endl;
 //assert((this->handlerState == State::UNINITIALIZED  && "Tried to initialize handler it's already initialized!"));

bool DiscordHandler::initialize() {
    if (handlerState != State::UNINITIALIZED) {
        return false;
    }
    DiscordEventHandlers handlers;
    memset(&handlers, 0, sizeof(handlers));
    handlers.ready = handleDiscordReady;
    handlers.disconnected = handleDiscordDisconnected;
    handlers.errored = handleDiscordError;

    Discord_Initialize("528564887992139817", &handlers, 1, NULL);
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

bool DiscordHandler::updatePresence() {
    if (handlerState != State::CONNECTED) {
        return false;
    }
    DiscordRichPresence discordPresence;
    memset(&discordPresence, 0, sizeof(discordPresence));
    discordPresence.state = presenceSettings.state.c_str();
    discordPresence.details = presenceSettings.details.c_str();
    discordPresence.startTimestamp = presenceSettings.startTimestamp;
    discordPresence.endTimestamp = presenceSettings.endTimestamp;
    discordPresence.largeImageKey = presenceSettings.largeImageKey.c_str();
    discordPresence.largeImageText = presenceSettings.largeImageText.c_str();
    discordPresence.smallImageKey = presenceSettings.smallImageKey.c_str();
    discordPresence.smallImageText = presenceSettings.smallImageText.c_str();
    //const char* partyId [NOT USED]
    discordPresence.partySize = presenceSettings.partySize;
    discordPresence.partyMax = presenceSettings.partyMax;
    //const char* matchSecret [NOT USED]
    //const char* joinSecret [NOT USED]
    //const char* spectateSecret [NOT USED]
    //int8_t instance [NOT USED]
    Discord_UpdatePresence(&discordPresence);
    return true;
}

bool DiscordHandler::clearPresenceInfo() {
    presenceSettings.clearAll(); // clear previous values.
    if (handlerState != State::CONNECTED) {
        return false;
    }
    Discord_ClearPresence();
    return true;
}

bool DiscordHandler::setState(const std::string& state, bool update) {
    presenceSettings.state = state;
    return update ? updatePresence() : false;
}

bool DiscordHandler::setDetails(const std::string& details, bool update) {
    presenceSettings.details = details;
    return update ? updatePresence() : false;
}

bool DiscordHandler::setImage(const std::string& image, bool large, bool update) {
    if (!image.empty() && !large && presenceSettings.largeImageKey.empty()) {
        std::cout << "[TIP] Small image won't be displayed if large image is not set!" << std::endl;
    }
    if (large) {
        presenceSettings.largeImageKey = image;
    } else {
        presenceSettings.smallImageKey = image;
    }
    return update ? updatePresence() : false;
}

bool DiscordHandler::setImageText(const std::string& text, bool large, bool update) {
    if (!text.empty() && ((large && presenceSettings.largeImageKey.empty()) || (!large && presenceSettings.smallImageKey.empty()))) {
        std::cout << "[TIP] Image tooltip won't be displayed if the image is not set!" << std::endl;
    }
    if (large) {
        presenceSettings.largeImageText = text;
    } else {
        presenceSettings.smallImageText = text;
    }
    return update ? updatePresence() : false;
}

bool DiscordHandler::setPartySize(const int partySize, const int partyMax, bool update) {
    if (partySize != -1 && presenceSettings.state.empty()) { // partySize: -1 = reset
        std::cout << "[TIP] Party size won't be displayed if state is not set!" << std::endl;
    }
    presenceSettings.partySize = partySize == -1 ? 0 : partySize;
    presenceSettings.partyMax = partyMax == 1 ? 0 : partyMax;
    return update ? updatePresence() : false;
}

bool DiscordHandler::setStartTimestamp(const int64_t timestamp, bool update) {
    presenceSettings.startTimestamp = timestamp == -1 ? 0 : timestamp;
    return update ? updatePresence() : false;
}

bool DiscordHandler::setEndTimestamp(const int64_t timestamp, bool update) {
    presenceSettings.endTimestamp = timestamp == -1 ? 0 : timestamp;
    return update ? updatePresence() : false;
}

void DiscordHandler::printNotConnectedErrorMessage() const {
    std::cout << "Cannot update to Discord because the client is not connected!" << std::endl;
    std::cout << "Try reinit Discord by calling \"reinitdiscord\" command." << std::endl;
}

DiscordHandler& DiscordHandler::getInstance() {
    static DiscordHandler instance;
    return instance;
}

bool DiscordHandler::isCallbackUpdate() {
    auto time = std::chrono::steady_clock::now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(time - lastCallbackUpdate);
    if (elapsedTime >= std::chrono::milliseconds(5000)) {
        lastCallbackUpdate = time;
        return true;
    }
    return false;
}

const std::atomic<DiscordHandler::State>& DiscordHandler::getHandlerState() const {
    return handlerState;
}

void DiscordHandler::handleDiscordReady(const DiscordUser* connectedUser) {
    printf("[Discord]: connected to user %s#%s - %s\n", connectedUser->username, connectedUser->discriminator, connectedUser->userId);
    getInstance().handlerState = State::CONNECTED;
    getInstance().updatePresence();
}

void DiscordHandler::handleDiscordDisconnected(int errcode, const char* message) {
    printf("[Discord]: disconnected (%d: %s)\n", errcode, message);
    getInstance().uninitialize();
}

void DiscordHandler::handleDiscordError(int errcode, const char* message) {
    printf("[Discord]: error (%d: %s)\n", errcode, message);
    getInstance().uninitialize();
}
