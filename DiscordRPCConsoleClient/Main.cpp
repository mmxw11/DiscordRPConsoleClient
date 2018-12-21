#include "pch.h"

#include "ICommand.h"
#include "TestCmd.h"

int main() {
    TestCmd cmd("test");
    ICommand& icmd = cmd;
    icmd.executeCommand(0, nullptr);
}