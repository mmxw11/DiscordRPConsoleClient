#include "pch.h"

#include "ApplicationManager.h"

int main() {
    //find discord instance
    //application id
    {
        ApplicationManager appManager;
        appManager.runApplication();
    }
    std::cout << "Bye" << std::endl;
    _CrtDumpMemoryLeaks();
}