#include "stdafx.h"
#include "TestReadConsole.h"
#include "Console.h"


TestReadConsole::TestReadConsole()
{
    test1();
}

void TestReadConsole::test1()
{
    HANDLE stdinput = GetStdHandle( STD_INPUT_HANDLE );
    HANDLE stdoutput = GetStdHandle( STD_OUTPUT_HANDLE );
    DWORD num_read = 0;
    wchar_t buf[1024] = { 0 };
    ReadConsoleW( stdinput, buf, 1024, &num_read, NULL );
    WriteConsoleW( stdoutput, buf, num_read, &num_read, 0 );
}
