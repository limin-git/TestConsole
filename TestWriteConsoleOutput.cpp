#include "stdafx.h"
#include "TestWriteConsoleOutput.h"
#include "Console.h"


TestWriteConsoleOutput::TestWriteConsoleOutput()
{
    test1();
}

void TestWriteConsoleOutput::test1()
{
    std::cout << "hello, world" << std::endl;
    _getch();
    Console::cls();
}
