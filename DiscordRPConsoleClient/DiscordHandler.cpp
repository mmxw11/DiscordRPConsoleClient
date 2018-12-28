#include "pch.h"

#include "DiscordHandler.h"
#include "Windows.h"

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
    this->initialized = false;
}