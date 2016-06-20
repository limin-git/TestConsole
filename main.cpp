// Console.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Console.h"
#include "TestCreateConsoleScreenBuffer.h"
#include "TestWriteConsole.h"
#include "TestReadConsoleInput.h"
#include "TestGetConsoleMode.h"
#include "TestSetConsoleMode.h"


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

    if ( 1 )
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

    _getch();
    return;
}
