#include "stdafx.h"
#include "TestWinEvents.h"


TestWinEvents::TestWinEvents()
: m_hook( NULL )
{
    CoInitialize(NULL);


    test1();
}


TestWinEvents::~TestWinEvents()
{
    if ( m_hook )
    {
        UnhookWinEvent( m_hook );
    }

    CoUninitialize();
}


VOID CALLBACK TestWinEvents::win_event_proc(
    HWINEVENTHOOK hWinEventHook,
    DWORD event,
    HWND hwnd,
    LONG idObject,
    LONG idChild,
    DWORD dwEventThread,
    DWORD dwmsEventTime )
{
    if ( event | EVENT_CONSOLE_CARET ) { std::cout << "EVENT_CONSOLE_CARET" << std::endl;}
    if ( event | EVENT_CONSOLE_END_APPLICATION ) { std::cout << "EVENT_CONSOLE_END_APPLICATION" << std::endl;}
    if ( event | EVENT_CONSOLE_LAYOUT ) { std::cout << "EVENT_CONSOLE_LAYOUT" << std::endl;}
    if ( event | EVENT_CONSOLE_START_APPLICATION ) { std::cout << "EVENT_CONSOLE_START_APPLICATION" << std::endl;}
    if ( event | EVENT_CONSOLE_UPDATE_REGION ) { std::cout << "EVENT_CONSOLE_UPDATE_REGION" << std::endl;}
    if ( event | EVENT_CONSOLE_UPDATE_SCROLL ) { std::cout << "EVENT_CONSOLE_UPDATE_SCROLL" << std::endl;}
    if ( event | EVENT_CONSOLE_UPDATE_SIMPLE ) { std::cout << "EVENT_CONSOLE_UPDATE_SIMPLE" << std::endl;}
}


void TestWinEvents::test1()
{
    m_hook = SetWinEventHook(
        EVENT_CONSOLE_CARET, EVENT_CONSOLE_END_APPLICATION, // Range of events (4 to 5).
        NULL,                                               // Handle to DLL.
        win_event_proc,                                     // The callback.
        0, 0,                                               // Process and thread IDs of interest (0 = all)
        WINEVENT_OUTOFCONTEXT | WINEVENT_SKIPOWNPROCESS);   // Flags.

    MSG msg;

    while(GetMessage(&msg, NULL, NULL, NULL))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}
