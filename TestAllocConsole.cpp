#include "stdafx.h"
#include "TestAllocConsole.h"
#include "Console.h"


TestAllocConsole::TestAllocConsole()
{
    test1();
}


void TestAllocConsole::test1()
{
    FreeConsole();
    AllocConsole();
    Sleep(1000);
    //Console::set_color( 0x3F );
    std::cout << "Hello, World!" << std::endl;
}
