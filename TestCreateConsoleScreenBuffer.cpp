#include "stdafx.h"
#include "TestCreateConsoleScreenBuffer.h"
#include "Console.h"


TestCreateConsoleScreenBuffer::TestCreateConsoleScreenBuffer()
{
    m_std_output_handle = GetStdHandle( STD_OUTPUT_HANDLE );
    m_cp = GetConsoleCP();
    m_output_cp = GetConsoleOutputCP();
}


TestCreateConsoleScreenBuffer::~TestCreateConsoleScreenBuffer()
{
    SetConsoleActiveScreenBuffer( m_std_output_handle );
    SetStdHandle( STD_OUTPUT_HANDLE, m_std_output_handle );
    SetConsoleCP( m_cp );
    SetConsoleOutputCP( m_output_cp );
}


void TestCreateConsoleScreenBuffer::create_buffer()
{
    std::wstring ws = L"hello, world!\n";

    // write something to std output
    WriteConsoleW( m_std_output_handle, ws.c_str(), ws.size(), 0, 0 );
    _getch();

    // create a new buffer
    HANDLE new_buffer = CreateConsoleScreenBuffer( GENERIC_READ | GENERIC_WRITE, 0, 0, CONSOLE_TEXTMODE_BUFFER, 0 );

    // activate it and replace std output handle
    SetConsoleActiveScreenBuffer( new_buffer );
    SetStdHandle( STD_OUTPUT_HANDLE, new_buffer );

    // write something to new buffer
    ws = L"中华人民共和国\n";
    SetConsoleOutputCP( 936 );
    HANDLE std_output_handle = GetStdHandle( STD_OUTPUT_HANDLE );
    WriteConsoleW( std_output_handle, ws.c_str(), ws.size(), 0, 0 );
    CloseHandle( new_buffer );

    _getch();
}


void TestCreateConsoleScreenBuffer::get_new_buffer_info()
{
    //HANDLE new_buffer = CreateConsoleScreenBuffer( GENERIC_READ | GENERIC_WRITE, 0, 0, CONSOLE_TEXTMODE_BUFFER, 0 );
    //GetConsoleScreenBufferInfo(  )
}

