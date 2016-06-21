#include "stdafx.h"
#include "TestWriteConsoleOutputCharacter.h"
#include "Console.h"


TestWriteConsoleOutputCharacter::TestWriteConsoleOutputCharacter()
    : cout( GetStdHandle( STD_OUTPUT_HANDLE ) ),
      cin( GetStdHandle( STD_INPUT_HANDLE ) )
{    
    //test1();
    //write_center_test();
    cls_test();
}


void TestWriteConsoleOutputCharacter::test1()
{
    std::cout << "hello, world" << std::endl;
    _getch();
    Console::cls2();
}


void TestWriteConsoleOutputCharacter::write_center( const std::string& s, HANDLE output )
{
    std::wstring ws = to_wstring( s, CP_UTF8 );
    std::string as = to_string( ws, 936 );

    DWORD written = 0;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo( output, &csbi );
    size_t window_width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    size_t window_height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    size_t pos = ( window_width * window_height - as.size() ) / 2;
    COORD coord = { pos % window_width, pos / window_width };
    WriteConsoleOutputCharacter( output, ws.c_str(), ws.size(), coord, &written );
}


void TestWriteConsoleOutputCharacter::write_center_test()
{
    HANDLE stdinput = GetStdHandle( STD_INPUT_HANDLE );
    HANDLE stdoutput = GetStdHandle( STD_OUTPUT_HANDLE );
    HANDLE new_handle = CreateConsoleScreenBuffer( GENERIC_READ | GENERIC_WRITE, 0, 0, CONSOLE_TEXTMODE_BUFFER, 0 );

    while ( true )
    {
        DWORD num_read = 0;
        wchar_t buf[1024] = { 0 };
        ReadConsoleW( stdinput, buf, 1024, &num_read, NULL );
        buf[num_read -1] = buf[num_read -2] = 0;
        std::string s = to_string( buf, CP_UTF8 );
        SetConsoleActiveScreenBuffer( new_handle );
        write_center( s, new_handle );
        _getch();
        Console::cls2( new_handle );
        SetConsoleActiveScreenBuffer( stdoutput );
    }
}


std::wstring TestWriteConsoleOutputCharacter::to_wstring( const std ::string& s, int code_page )
{
    const size_t size = 1024 * 1024;
    static wchar_t buffer[ size];
    MultiByteToWideChar( code_page , 0, s. c_str(), - 1, buffer , size );
    return std ::wstring( buffer );
}


std::string TestWriteConsoleOutputCharacter::to_string( const std ::wstring& ws, int code_page )
{
    const size_t size = 1024 * 1024;
    static char buffer[ size];
    WideCharToMultiByte( code_page , 0, ws. c_str(), - 1, buffer , size, 0, 0 );
    return std ::string( buffer );
}


void TestWriteConsoleOutputCharacter::cls( HANDLE output )
{
    DWORD written = 0;
    COORD coord = { 0, 0 };
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo( output, &csbi );
    std::wstring ws( csbi.dwSize.X * csbi.dwSize.Y, L' ' );
    WriteConsoleOutputCharacterW( output, ws.c_str(), ws.size(), coord, &written );
    SetConsoleCursorPosition( output, coord );
}


void TestWriteConsoleOutputCharacter::cls_test()
{
    std::cout << "will clear screen" << std::endl;
    _getch();
    cls( cout );
    _getch();
    std::cout << "hello, world!" << std::endl;
}
