#include "pch.h"

#include "DiscordHandler.h"
#include "discord-rpc/discord_rpc.h"
#include <assert.h>

// Link the Discord library.
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

void DiscordHandler::setApplicationId(const std::string& applicationId) {
    this->applicationId = applicationId;
}

bool DiscordHandler::initialize() {
    if (handlerState != State::UNINITIALIZED) {
        return false;
    }
    assert(!applicationId.empty());
    DiscordEventHandlers handlers;
    memset(&handlers, 0, sizeof(handlers));
    handlers.ready = handleDiscordReady;
    handlers.disconnected = handleDiscordDisconnected;
    handlers.errored = handleDiscordError;
    handlers.joinGame = handleDiscordJoin;
    handlers.spectateGame = handleDiscordSpectate;
    handlers.joinRequest = handleDiscordJoinRequest;
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
    discordPresence.partyId = presenceSettings.partyId.c_str();
    discordPresence.partySize = presenceSettings.partySize;
    discordPresence.partyMax = presenceSettings.partyMax;
    discordPresence.joinSecret = presenceSettings.joinSecret.c_str();
    if (presenceSettings.displaySpectateInfo) {
        discordPresence.spectateSecret = "SPECTATE-SECRET-PLACEHOLDER"; // This can be just anything.
    }
    Discord_UpdatePresence(&discordPresence);
    return true;
}

bool DiscordHandler::clearPresenceInfo() {
    presenceSettings.clearAll(); // Clear previous values.
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
    // Tips.
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
    // Tips.
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
    // Tips.
    if (partySize != -1) { // partySize: -1 = reset
        if (presenceSettings.state.empty()) {
            std::cout << "[TIP] Party size won't be displayed on your profile if state is not set!" << std::endl;
        }
        if (partySize > partyMax && (!presenceSettings.partyId.empty() || presenceSettings.displaySpectateInfo)) {
            std::cout << "[TIP] Game join and spectate invites will expire when party size is more than party max!" << std::endl;
        }
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

bool DiscordHandler::setGameJoinInfo(const std::string& id, bool update) {
    // Tips.
    if (!id.empty() && presenceSettings.partySize > presenceSettings.partyMax) { // partySize more than max.
        std::cout << "[TIP] You can't send game join invites when party size is more than party max!" << std::endl;
    }
    presenceSettings.partyId = id;
    if (id.empty()) {
        presenceSettings.joinSecret = "";
    } else {
        presenceSettings.joinSecret = id;
        mangleDiscordSecret(presenceSettings.joinSecret);
    }
    return update ? updatePresence() : false;
}

bool DiscordHandler::setSpectateInfo(const bool show, bool update) {
    // Tips.
    if (show) {
        if (presenceSettings.partySize > presenceSettings.partyMax) { // partySize more than max.
            std::cout << "[TIP] You can't send spectate invites when party size is more than party max!" << std::endl;
        }
        if (!presenceSettings.partyId.empty()) { // Spectate invites tied to partyId.
            std::cout << "[TIP] If you change partyId, spectate invites may reset!" << std::endl;
        }
    }
    presenceSettings.displaySpectateInfo = show;
    return update ? updatePresence() : false;
}

void DiscordHandler::printNotConnectedErrorMessage() const {
    std::cout << "Can't send data to Discord because the client is not connected!" << std::endl;
    std::cout << "Try reinit Discord connection by calling \"reinitdiscord\" command." << std::endl;
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

void DiscordHandler::mangleDiscordSecret(std::string& secret) {
    char key[] = { "Super_secret_discord_key" };
    for (int i = 0; i < secret.size(); i++) {
        secret[i] = secret[i] ^ key[i % (sizeof(key) / sizeof(char))];
    }
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

void DiscordHandler::handleDiscordJoin(const char* secret) {
    printf("[Discord]: You clicked on someone's game invitation. (joinSecret: %s).\n", secret);
    std::string partyId = secret;
    getInstance().mangleDiscordSecret(partyId);
    printf("[Discord]: Joining to their party... setting game join visibility to \"show\" with the partyId of \"%s\".", partyId.c_str());
    getInstance().setGameJoinInfo(partyId, true);
}

void DiscordHandler::handleDiscordSpectate(const char* secret) {
    printf("[Discord]: You clicked on someone's spectate invitation. Nothing will happen because it's just a dummy invite (spectateSecret: %s).\n", secret);
}

void DiscordHandler::handleDiscordJoinRequest(const DiscordUser* request) {
    printf("[Discord]: Received join request from %s#%s - %s\n", request->username, request->discriminator, request->userId);
    int response = DISCORD_REPLY_NO;
    do {
        printf("Accept? (y/n)");
        std::string input;
        std::getline(std::cin, input);
        if (!std::cin.good()) {
            // Unexpected input. (ctrl + c/break for example)
            std::cin.clear();
            break;
        }
        if (input != "y" && input != "n") {
            continue;
        }
        response = input == "y" ? DISCORD_REPLY_YES : DISCORD_REPLY_NO;
        break;
    } while (1);
    printf("[Discord]: Responding to %s#%s's join request with \"%s\" because it's a dummy invite.\n", request->username, request->discriminator, response == 0 ? "DISCORD_REPLY_NO" : "DISCORD_REPLY_YES");
    Discord_Respond(request->userId, DISCORD_REPLY_NO);
}