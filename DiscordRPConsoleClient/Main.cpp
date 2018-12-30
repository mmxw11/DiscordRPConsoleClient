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
    if (appManager == nullptr) {
        return FALSE;
    }
    appManager->shutdown();
    return TRUE;
}

int main() {
    // set handler for shutdown.
    if (!SetConsoleCtrlHandler(ctrlHandler, TRUE)) {
        printf("\nERROR: Could not set control handler.");
        return 1;
    }//MAY TAKE A WHILE TO UPDATE WARNING
    //find discord instance
    //application id
    std::cout << "Use \"HELP\" command to see a list of available commands." << std::endl;
    std::cout << std::endl;
    {
        //TODO: do something about console getting overridden
        ApplicationManager appManagerInstance;
        ::appManager = &appManagerInstance;
        appManagerInstance.runApplication();
        //  appManagerInstance.shutdown();
    }
    std::cout << "Bye" << std::endl;
    _CrtDumpMemoryLeaks();
    return 0;
}