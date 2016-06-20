#pragma once


class TestWriteConsoleOutputCharacter
{
public:

    TestWriteConsoleOutputCharacter();

    void test1();

public:

    void write_center( const std::string& s, HANDLE output );
    void write_center_test();

public:

    static std::wstring to_wstring( const std ::string& s, int code_page );
    static std::string to_string( const std ::wstring& ws, int code_page );
};
