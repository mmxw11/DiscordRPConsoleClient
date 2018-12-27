#include "pch.h"

#include "ApplicationManager.h"

int main() {
    //find discord instance
    //application id

    //TODO: 
    // split register commands [DONE]
    // second constructor to command manager
    // remove testcmd and comments from command manager [DONE]
    // rename project [DONE]
    // command aliases [WILL NOT IMPLEMENT]
    // command manager dispatch [DONE]
    // register new command [DONE]
    // Start messages/settings before runapplication is called
    // exit and help commands [DONE]
    {
        ApplicationManager appManager;
        appManager.runApplication();
    }
    std::cout << "Bye" << std::endl;
    _CrtDumpMemoryLeaks();
}