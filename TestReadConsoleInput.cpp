#include "stdafx.h"
#include "TestReadConsoleInput.h"
#include "TestGetConsoleMode.h"
#include "Console.h"


TestReadConsoleInput::TestReadConsoleInput()
{
    if ( 0 )
    {
        test1();
    }
    else
    {
        while ( true )
        {
            std::string cmd = wait_review();
            if ( cmd.empty() )
            {
                cmd = "next";
            }
            std::cout << cmd << std::endl;
        }
    }
}

static void DisbleQuickEditMode()
{
    HANDLE stdinput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(stdinput, &mode);
    mode &= ~ENABLE_QUICK_EDIT_MODE;
    SetConsoleMode(stdinput, mode);
}

void TestReadConsoleInput::test1()
{
    HANDLE stdinput = GetStdHandle(STD_INPUT_HANDLE); 
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE); 
    DWORD fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT; 
    //DWORD fdwMode = ENABLE_MOUSE_INPUT; 
    INPUT_RECORD input_buffer[128]; 
    DWORD num_read = 0;

    Console::disable_console_mode( ENABLE_QUICK_EDIT_MODE  );
    SetConsoleMode( stdinput, fdwMode );
    //SetConsoleMode( stdinput, ENABLE_WINDOW_INPUT );
    //SetConsoleMode( hStdout, ENABLE_WINDOW_INPUT );
    //GetConsoleMode( stdinput, &fdwMode );
    //TestGetConsoleMode::print_mode( std::cout, fdwMode );

    while ( true ) 
    { 
        // Wait for the events. 
        ReadConsoleInput( stdinput, input_buffer, 128, &num_read );
 
        for ( size_t i = 0; i < num_read; i++) 
        {
            //std::cout << input_buffer[i].EventType << std::endl;

            switch( input_buffer[i].EventType ) 
            { 
                case KEY_EVENT: // keyboard input 
                    on_key_event( input_buffer[i].Event.KeyEvent );
                    break; 
 
                case MOUSE_EVENT: // mouse input
                    on_mouse_event( input_buffer[i].Event.MouseEvent );
                    break; 
 
                case WINDOW_BUFFER_SIZE_EVENT: // scrn buf. resizing 
                    break; 
 
                case FOCUS_EVENT:  // disregard focus events 
                    break;

                case MENU_EVENT:   // disregard menu events 
                    break; 
 
                default: 
                    break; 
            } 
        }
    }

}


void TestReadConsoleInput::on_mouse_event( const MOUSE_EVENT_RECORD& e )
{
    switch (e.dwEventFlags)
    {
    case 0:
        //printf("button press\n");
        switch( e.dwButtonState )
        {
        case FROM_LEFT_1ST_BUTTON_PRESSED:
            printf("left button clicked (%d, %d)\n", e.dwMousePosition.X, e.dwMousePosition.Y );
            break;
        case RIGHTMOST_BUTTON_PRESSED:
            printf("right button clicked (%d, %d)\n", e.dwMousePosition.X, e.dwMousePosition.Y );
            break;
        default:
            //printf("unknown\n");
            break;
        }
        break;
    case DOUBLE_CLICK:
        printf("double click (%d, %d)\n", e.dwMousePosition.X, e.dwMousePosition.Y );
        break;
    case MOUSE_HWHEELED:
        printf("horizontal mouse wheel (%d, %d)\n", e.dwMousePosition.X, e.dwMousePosition.Y );
        break;
    case MOUSE_MOVED:
        //printf("mouse moved\n");
        break;
    case MOUSE_WHEELED:
        printf("vertical mouse wheel (%d, %d)\n", e.dwMousePosition.X, e.dwMousePosition.Y );
        break;
    default:
        //printf("unknown\n");
        break;
    }
}


void TestReadConsoleInput::on_key_event( const KEY_EVENT_RECORD& e )
{
    std::cout << "key " << ( e.bKeyDown ? "down" : "up" ) << std::endl;
    //std::cout << "repeat " << e.wRepeatCount << std::endl;
    if ( e.bKeyDown )
    {
        if ( isprint( e.uChar.AsciiChar ) )
        {
            std::cout << e.uChar.AsciiChar << std::endl;
        }
        else
        {
            std::cout << std::setw(2) << std::hex << e.wVirtualKeyCode << std::endl;
        }
    }
}


std::string TestReadConsoleInput::wait_review()
{
    HANDLE stdinput = GetStdHandle(STD_INPUT_HANDLE); 
    INPUT_RECORD input_buffer[128]; 
    DWORD num_read = 0;

    Console::disable_console_mode( ENABLE_QUICK_EDIT_MODE  );
    SetConsoleMode( stdinput, ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT );

    while ( true ) 
    { 
        ReadConsoleInput( stdinput, input_buffer, 128, &num_read );

        for ( size_t i = 0; i < num_read; i++) 
        {
            switch( input_buffer[i].EventType ) 
            { 
            case KEY_EVENT:
                {
                    KEY_EVENT_RECORD& e = input_buffer[i].Event.KeyEvent;
                    if ( e.bKeyDown )
                    {
                        switch ( e.wVirtualKeyCode )
                        {
                        case VK_DELETE:         // Del
                            return "delete";
                        case VK_ESCAPE:         // Esc
                            return "quit";
                        case VK_LEFT:           // Left
                        case VK_UP:             // Up
                        case VK_PRIOR:          // PgUp
                        case VK_BROWSER_BACK:   // Back
                        case VK_OEM_MINUS:      // -
                        case VK_OEM_4:          // [{
                        case VK_OEM_1:          //;:
                        case VK_OEM_COMMA:      // ,<
                            return "back";
                        }
                        return "";
                    }
                    break;
                }
            case MOUSE_EVENT:
                {
                    MOUSE_EVENT_RECORD& e = input_buffer[i].Event.MouseEvent;
                    switch (e.dwEventFlags)
                    {
                    case 0:
                        switch( e.dwButtonState )
                        {
                        case RIGHTMOST_BUTTON_PRESSED:
                            return "back";
                        case FROM_LEFT_1ST_BUTTON_PRESSED:
                            return "";
                        }
                        break;
                    case DOUBLE_CLICK:
                    case MOUSE_HWHEELED:
                    case MOUSE_WHEELED:
                        return "";
                    case MOUSE_MOVED:
                    default:
                        break;
                    }
                    break;
                }
            } 
        }
    }

    return "";
}
