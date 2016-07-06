#include "stdafx.h"
#include "TestGetConsoleWindow.h"


TestGetConsoleWindow::TestGetConsoleWindow()
{
    //test1();
    test2();
}


void TestGetConsoleWindow::test1()
{
    // no sizing border, can not change size
    HWND hwnd = GetConsoleWindow();
    LONG style = GetWindowLong( hwnd, GWL_STYLE );
    style &= ~WS_SIZEBOX;
    SetWindowLong( hwnd, GWL_STYLE, style );
}


void TestGetConsoleWindow::test2()
{
    // can not change size
    HWND hwnd = GetConsoleWindow();
    LONG style = GetWindowLong( hwnd, GWL_STYLE );
    style &= ~(WS_CAPTION|WS_SYSMENU);
    SetWindowLong( hwnd, GWL_STYLE, style );
    //SetConsoleWindowInfo( )
    //DrawWindo( hwnd );
}
