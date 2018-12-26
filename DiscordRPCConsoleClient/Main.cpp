#include "pch.h"

#include "ApplicationManager.h"
/*#include "ICommand.h"
#include "TestCmd.h"*/

int main() {
    //find discord instance
    //application id
    ApplicationManager appManager;
    appManager.runApplication();
    std::cout << "Bye" << std::endl;
    /**
    TestCmd cmd(appManager, "test");
    ICommand& icmd = cmd;
    icmd.executeCommand(args2, 2);*/
}