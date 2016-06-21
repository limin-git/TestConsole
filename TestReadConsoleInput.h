#pragma once


class TestReadConsoleInput
{
public:

    TestReadConsoleInput();

    void test1();

    std::string wait_review();
    void        wait_review_test();
    void        wait_review_test_2();

public:

    static void on_mouse_event( const MOUSE_EVENT_RECORD& e );
    static void on_key_event( const KEY_EVENT_RECORD& e );

};
