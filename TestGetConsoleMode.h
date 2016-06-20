#pragma once


class TestGetConsoleMode
{
public:

    TestGetConsoleMode();

    void test1();

public:

    static std::ostream& print_mode( std::ostream& os, DWORD mode );

};
