#include "stdafx.h"
#include "TestSetConsoleMode.h"
#include "TestGetConsoleMode.h"


TestSetConsoleMode::TestSetConsoleMode()
{
    test1();
}


void TestSetConsoleMode::test1()
{
    DWORD input_mode = 0;
    DWORD output_mode = 0;
    HANDLE input = GetStdHandle( STD_INPUT_HANDLE );
    HANDLE output = GetStdHandle( STD_OUTPUT_HANDLE );

    //return os
    //    << "ENABLE_ECHO_INPUT       : " << ( 0 == (mode & ENABLE_ECHO_INPUT) ) << std::endl
    //    << "ENABLE_INSERT_MODE      : " << ( 0 == (mode & ENABLE_INSERT_MODE) ) << std::endl
    //    << "ENABLE_LINE_INPUT       : " << ( 0 == (mode & ENABLE_LINE_INPUT) ) << std::endl
    //    << "ENABLE_MOUSE_INPUT      : " << ( 0 == (mode & ENABLE_MOUSE_INPUT) ) << std::endl
    //    << "ENABLE_PROCESSED_INPUT  : " << ( 0 == (mode & ENABLE_PROCESSED_INPUT) ) << std::endl
    //    << "ENABLE_QUICK_EDIT_MODE  : " << ( 0 == (mode & ENABLE_QUICK_EDIT_MODE) ) << std::endl
    //    << "ENABLE_WINDOW_INPUT     : " << ( 0 == (mode & ENABLE_WINDOW_INPUT) ) << std::endl;
    
    std::cout << "input mode:" << std::endl;

    if ( 0 == SetConsoleMode( input, input_mode ) ) { std::cout << "failed" << std::endl; }
    GetConsoleMode( input, &input_mode );
    TestGetConsoleMode::print_mode( std::cout, input_mode ); std::cout << std::endl;

    if ( 0 == SetConsoleMode( input, ENABLE_ECHO_INPUT ) ) { std::cout << "failed set ENABLE_ECHO_INPUT" << std::endl; }
    GetConsoleMode( input, &input_mode );
    TestGetConsoleMode::print_mode( std::cout, input_mode ); std::cout << std::endl;

    if ( 0 == SetConsoleMode( input, ENABLE_INSERT_MODE ) ) { std::cout << "failed set ENABLE_INSERT_MODE" << std::endl; }
    GetConsoleMode( input, &input_mode );
    TestGetConsoleMode::print_mode( std::cout, input_mode ); std::cout << std::endl;

    if ( 0 == SetConsoleMode( input, ENABLE_LINE_INPUT ) ) { std::cout << "failed set ENABLE_LINE_INPUT" << std::endl; }
    GetConsoleMode( input, &input_mode );
    TestGetConsoleMode::print_mode( std::cout, input_mode ); std::cout << std::endl;

    if ( 0 == SetConsoleMode( input, ENABLE_LINE_INPUT ) ) { std::cout << "failed set ENABLE_MOUSE_INPUT" << std::endl; }
    GetConsoleMode( input, &input_mode );
    TestGetConsoleMode::print_mode( std::cout, input_mode ); std::cout << std::endl;

    if ( 0 == SetConsoleMode( input, ENABLE_LINE_INPUT ) ) { std::cout << "failed set ENABLE_PROCESSED_INPUT" << std::endl; }
    GetConsoleMode( input, &input_mode );
    TestGetConsoleMode::print_mode( std::cout, input_mode ); std::cout << std::endl;

    if ( 0 == SetConsoleMode( input, ENABLE_LINE_INPUT ) ) { std::cout << "failed set ENABLE_QUICK_EDIT_MODE" << std::endl; }
    GetConsoleMode( input, &input_mode );
    TestGetConsoleMode::print_mode( std::cout, input_mode ); std::cout << std::endl;

    if ( 0 == SetConsoleMode( input, ENABLE_LINE_INPUT ) ) { std::cout << "failed set ENABLE_WINDOW_INPUT" << std::endl; }
    GetConsoleMode( input, &input_mode );
    TestGetConsoleMode::print_mode( std::cout, input_mode ); std::cout << std::endl;
}
