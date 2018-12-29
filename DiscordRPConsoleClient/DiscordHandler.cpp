#include "pch.h"

#include "DiscordHandler.h"
#include "discord-rpc/discord_rpc.h"

// link discord library
#if defined(_WIN64)
#pragma comment(lib, "discord-rpc-win64.lib")
#else
#pragma comment(lib, "discord-rpc-win32.lib")
#endif

DiscordHandler::DiscordHandler() {
}

DiscordHandler::~DiscordHandler() {
    shutdown();
}

void DiscordHandler::init() {
}

void DiscordHandler::shutdown() {
    if (!initialized) {
        return;
    }
    std::cout << "Discord RP Client shutdown!" << std::endl;
    Discord_Shutdown();
    this->initialized = false;
}