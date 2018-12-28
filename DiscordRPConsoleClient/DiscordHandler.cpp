#include "pch.h"

#include "DiscordHandler.h"
#include "discord-rpc/discord_rpc.h"
#include "Windows.h"

// link discord library
#if defined(_WIN64)
#pragma comment(lib, "discord-rpc-win64.lib")
#else
#pragma comment(lib, "discord-rpc-win32.lib")
#endif

DiscordHandler::DiscordHandler() {
    OutputDebugString(L"DiscordHandler constructor\n");
}

DiscordHandler::~DiscordHandler() {
    shutdown();
    OutputDebugString(L"DiscordHandler destructor\n");
}

void DiscordHandler::init() {
}

void DiscordHandler::shutdown() {
    if (!initialized) {
        // return;
    }
    OutputDebugString(L"Discord RP Client shutdown!\n");
    Discord_Shutdown();
    this->initialized = false;
}