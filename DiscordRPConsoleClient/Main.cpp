#include "pch.h"

#include "ApplicationManager.h"
#include <Windows.h>

static ApplicationManager* appManager;

static BOOL WINAPI ctrlHandler(DWORD dwCtrlType) {
    if (dwCtrlType != CTRL_CLOSE_EVENT &&
        dwCtrlType != CTRL_LOGOFF_EVENT &&
        dwCtrlType != CTRL_SHUTDOWN_EVENT &&
        dwCtrlType != CTRL_C_EVENT &&
        dwCtrlType != CTRL_BREAK_EVENT) {
        return FALSE;
    }
    if (!appManager) {
        return FALSE;
    }
    appManager->shutdown();
    return TRUE;
}

int main(int argc, char** argv) {
    // Memory leak detection. (Visual Studio debugger)
#if defined(_DEBUG) && defined(_MSC_VER)
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
    std::cout << "DiscordRPConsole client [Version 1.1]" << std::endl;
    std::cout << "Control Discord Rich Presence easily from command line.\n" << std::endl;
    // Set handler for shutdown.
    if (!SetConsoleCtrlHandler(ctrlHandler, TRUE)) {
        printf("\nERROR: Could not set control handler.");
        return 1;
    }
    // Parse applicationId.
    std::string applicationId;
    bool hasApplicationCmdArg = false;
    // Check command line args.
    for (int i = 0; i < argc; i++) {
        if (std::string(argv[i]) != "--applicationId") {
            continue;
        }
        if (i + 1 < argc) {
            hasApplicationCmdArg = true;
            applicationId = std::string(argv[i + 1]);
        }
        break;
    }
    if (!hasApplicationCmdArg) {
        // Ask for applicationId.
        std::cout << "You can also pass the applicationId as a command line argument using the --applicationId command option." << std::endl;
        std::cout << "Enter the applicationId: ";
        std::getline(std::cin, applicationId);
        if (!std::cin.good()) {
            printf("\nERROR: Unexpected input.");
            return 1;
        }
        std::cout << std::endl;
    }
    if (applicationId[0] == '\0') {
        printf("\nERROR: applicationId cannot be empty!");
        return 1;
    }
    // Initialize.
    std::cout << "Connecting to Discord with the applicationId of \"" << applicationId << "\".\nIf nothing happens check the spelling and make sure your Discord client is running." << std::endl;
    std::cout << "\nUse \"HELP\" command to see a list of available commands." << std::endl;
    try {
        ApplicationManager appManagerInstance;
        ::appManager = &appManagerInstance;
        appManagerInstance.runApplication(applicationId);
        std::cout << "Bye." << std::endl;
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cout << "Unknown error." << std::endl;
        return 1;
    }
    return 0;
}