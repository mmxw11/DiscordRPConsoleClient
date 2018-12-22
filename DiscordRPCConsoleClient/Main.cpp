#include "pch.h"

#include "ApplicationManager.h"
#include "ICommand.h"
#include "TestCmd.h"

int main() {
    const char *args[] = { "test","test2" };
    std::string args2[] = { "Hey", "Moi" };
    std::string* args5 = args2;
    std::cout << *(args5 + 1) << std::endl;

    ApplicationManager appManager;
    TestCmd cmd(appManager, "test");
    ICommand& icmd = cmd;
    icmd.executeCommand(args2, 2);
}