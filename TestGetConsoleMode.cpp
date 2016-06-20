#include "stdafx.h"
#include "TestGetConsoleMode.h"


TestGetConsoleMode::TestGetConsoleMode()
{
    test1();
}


void TestGetConsoleMode::test1()
{
    DWORD input_mode = 0;
    DWORD output_mode = 0;
    HANDLE input = GetStdHandle( STD_INPUT_HANDLE );
    HANDLE output = GetStdHandle( STD_OUTPUT_HANDLE );

    GetConsoleMode( input, &input_mode );
    std::cout << "input mode:" << std::endl;
    print_mode( std::cout, input_mode );

    GetConsoleMode( output, &output_mode );
    std::cout << "output mode:" << std::endl;
    print_mode( std::cout, output_mode );
}


std::ostream& TestGetConsoleMode::print_mode( std::ostream& os, DWORD mode )
{
    return os
        << "ENABLE_ECHO_INPUT       : " << ( 0 != (mode & ENABLE_ECHO_INPUT) ) << std::endl
        << "ENABLE_INSERT_MODE      : " << ( 0 != (mode & ENABLE_INSERT_MODE) ) << std::endl
        << "ENABLE_LINE_INPUT       : " << ( 0 != (mode & ENABLE_LINE_INPUT) ) << std::endl
        << "ENABLE_MOUSE_INPUT      : " << ( 0 != (mode & ENABLE_MOUSE_INPUT) ) << std::endl
        << "ENABLE_PROCESSED_INPUT  : " << ( 0 != (mode & ENABLE_PROCESSED_INPUT) ) << std::endl
        << "ENABLE_QUICK_EDIT_MODE  : " << ( 0 != (mode & ENABLE_QUICK_EDIT_MODE) ) << std::endl
        << "ENABLE_WINDOW_INPUT     : " << ( 0 != (mode & ENABLE_WINDOW_INPUT) ) << std::endl;
}
