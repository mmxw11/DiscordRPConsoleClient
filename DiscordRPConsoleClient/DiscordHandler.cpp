#include "pch.h"

#include "DiscordHandler.h"
#include <thread>
#include <Windows.h>
#include "discord-rpc/discord_rpc.h"

// link discord library
#if defined(_WIN64)
#pragma comment(lib, "discord-rpc-win64.lib")
#else
#pragma comment(lib, "discord-rpc-win32.lib")
#endif

DiscordRichPresence DiscordHandler::discordPresence;

DiscordHandler::DiscordHandler() :
    handlerState(State::UNINITIALIZED) {
    // memset(&discordPresence, 0, sizeof(discordPresence));
}

DiscordHandler::~DiscordHandler() {
    uninitialize();
}

/**
TODO:
remove app id from init and own function for it (+ ask at startup)
disconnect command
connect command
reset presence command

const char* state;
const char* details;

DONT SEND ENDTIMESTAMP WITHOUT STATE OR YOUR DISCORD CRASHES!
int64_t startTimestamp;
int64_t endTimestamp;
ONLY START -> Elpsed
ONLY END -> Remaining
BOTH -> Time left

const char* largeImageKey;
const char* largeImageText;

----YOU MUST HAVE LARGE IMAGE TO DISPLAY THESE:---
const char* smallImageKey;
const char* smallImageText;
--------------------------------------------------

const char* partyId; [NOT REQUIRED]

----YOU MUST SEND STATE TO DISPLAY THESE:---
MUST BE SENT AT THE SAME TIME!
int partySize,
int partyMax;
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

bool DiscordHandler::clearPresenceInfo() {
    memset(&discordPresence, 0, sizeof(discordPresence)); // clear previous values.
    if (handlerState != State::CONNECTED) {
        return false;
    }
    Discord_ClearPresence();
    return true;
}

bool DiscordHandler::setStatus(const char* status) {
    discordPresence.state = status;
    return updatePresence();
}

void DiscordHandler::printNotConnectedErrorMessage() const {
    std::cout << "Cannot update to Discord because the client is not connected!" << std::endl;
    std::cout << "Try reinit Discord by calling \"reinitdiscord\" command." << std::endl;
}

bool DiscordHandler::updatePresence() {
    if (handlerState != State::CONNECTED) {
        return false;
    }
    Discord_UpdatePresence(&discordPresence);
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
