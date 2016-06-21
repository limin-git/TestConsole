// Console.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Console.h"
#include "TestCreateConsoleScreenBuffer.h"
#include "TestWriteConsole.h"
#include "TestReadConsoleInput.h"
#include "TestGetConsoleMode.h"
#include "TestSetConsoleMode.h"
#include "TestWriteConsoleOutput.h"
#include "TestWriteConsoleOutputCharacter.h"
#include "TestReadConsole.h"
#include "TestWinEvents.h"


void main()
{
    if ( 0 )
    {
        TestCreateConsoleScreenBuffer test;
        test.create_buffer();
    }

    if ( 0 )
    {
        TestWriteConsole test;
    }

    if ( 0 )
    {
        TestReadConsoleInput test;
    }

    if ( 0 )
    {
        TestGetConsoleMode test;
    }

    if ( 0 )
    {
        TestSetConsoleMode test;
    }

    if ( 0 )
    {
        TestWriteConsoleOutput test;
    }

    if ( 0 )
    {
        TestWriteConsoleOutputCharacter test;
    }

    if ( 0 )
    {
        TestReadConsole test;
    }

    if ( 1 )
    {
        TestWinEvents test;
    }

    _getch();
    return;
}
