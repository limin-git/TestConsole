#pragma once


class TestWriteConsoleOutputCharacter
{
public:

    TestWriteConsoleOutputCharacter();

    void test1();

public:

    void write_center( const std::string& s, HANDLE output );
<<<<<<< HEAD
    void write_center_test();
    void cls( HANDLE output );
    void cls_test();
=======
    void write_center_test_1();
    void write_center_test_2();
>>>>>>> origin/master

public:

    static std::wstring to_wstring( const std ::string& s, int code_page );
    static std::string to_string( const std ::wstring& ws, int code_page );

public:

    HANDLE cout;
    HANDLE cin;
};
