// Console.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Console.h"
#include "TestCreateConsoleScreenBuffer.h"

//HANDLE std_output = GetStdHandle( STD_OUTPUT_HANDLE );
//HANDLE std_input = GetStdHandle( STD_INPUT_HANDLE );
//㘵


void test_buffer()
{
    HANDLE stdoutput = Console::stdoutput();

    HANDLE new_buffer = CreateConsoleScreenBuffer(
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL, CONSOLE_TEXTMODE_BUFFER,
        NULL );

    SetConsoleActiveScreenBuffer( new_buffer );

    Console::set_window( 50, 20, new_buffer );

    CHAR_INFO ch;
    ch.Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
    ch.Char.UnicodeChar = L' ';
    CHAR_INFO buffer[ 200 * 30 ];

    for ( size_t i = 0; i < 200 * 30; ++i )
    {
        buffer[i] = ch;
    }

    COORD buffer_size = { 200, 30 };
    COORD buffer_coord = { 0, 0 };
    SMALL_RECT write_region = { 0, 0, 200, 40 };

    WriteConsoleOutputW(
        new_buffer,
        buffer,
        buffer_size,
        buffer_coord,
        &write_region );

    int c1 = _getch();

    Console::set_font( 14, L"新宋体", new_buffer );

    std::wstring ws = L"㘵中华人民共和国abc\n";

    WriteConsoleW( new_buffer, ws.c_str(), ws.size(), NULL, NULL );

    {
        CONSOLE_SCREEN_BUFFER_INFO the_buffer;
        GetConsoleScreenBufferInfo( new_buffer, &the_buffer );
        std::stringstream strm;
        strm << the_buffer;
        std::string s = strm.str();
        //std::cout << the_buffer << std::endl;
        WriteConsoleA( new_buffer, s.c_str(), s.size(), NULL, NULL );
    }

    int c = _getch();
    SetConsoleActiveScreenBuffer( stdoutput );
}




void main()
{
    {
        TestCreateConsoleScreenBuffer test;
        test.create_buffer();
    }

    _getch();
    return;
}
