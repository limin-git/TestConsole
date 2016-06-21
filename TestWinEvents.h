#pragma once


class TestWinEvents
{
public:

    TestWinEvents();
    ~TestWinEvents();

    void test1();

public:

    static VOID CALLBACK win_event_proc(
        HWINEVENTHOOK hWinEventHook,
        DWORD event,
        HWND hwnd,
        LONG idObject,
        LONG idChild,
        DWORD dwEventThread,
        DWORD dwmsEventTime );

    HWINEVENTHOOK m_hook;
};
