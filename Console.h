#pragma once


//HANDLE std_output = GetStdHandle( STD_OUTPUT_HANDLE );
//HANDLE std_input = GetStdHandle( STD_INPUT_HANDLE );


class Console
{
public:

    static HANDLE stdoutput()
    {
        static HANDLE output = GetStdHandle( STD_OUTPUT_HANDLE );
        return output;
    }

    static HANDLE stdinput()
    {
        static HANDLE input = GetStdHandle( STD_INPUT_HANDLE );
        return input;
    }

    static void show_cursor( BOOL visible = true, HANDLE output_handle = stdoutput() )
    {
        CONSOLE_CURSOR_INFO cursor_info;
        GetConsoleCursorInfo( output_handle, &cursor_info );

        if ( visible != cursor_info.bVisible )
        {
            cursor_info.bVisible = visible;
            SetConsoleCursorInfo( output_handle, &cursor_info );
        }
    }

    static void fix_utf8_output( HANDLE output_handle = stdoutput() )
    {
        CONSOLE_SCREEN_BUFFER_INFO csbinfo;
        GetConsoleScreenBufferInfo( output_handle, &csbinfo );
        COORD coord = { 0, 0 };
        CHAR_INFO chiFill;
        chiFill.Char.UnicodeChar = L' ';
        ScrollConsoleScreenBuffer( output_handle, &csbinfo.srWindow, NULL, coord, &chiFill  );
    }

    static void print_font_info( HANDLE output_handle = stdoutput() )
    {
        CONSOLE_FONT_INFOEX f;
        f.cbSize = sizeof( CONSOLE_FONT_INFOEX );

        if ( 0 == GetCurrentConsoleFontEx( output_handle, TRUE, &f ) )
        {
            std::cout << "failed: " << GetLastError() << std::endl;
            return;
        }

        std::wcout
            << L"nFont     : " << f.nFont << std::endl
            << L"dwFontSize: " << f.dwFontSize.X << L"," << f.dwFontSize.Y << std::endl
            << L"FontFamily: " << f.FontFamily << std::endl
            << L"FontWeight: " << f.FontWeight << std::endl
            << L"FaceName  : " << f.FaceName << std::endl;
    }

    static void set_font( SHORT font_size = 14, const std::wstring& face_name = L"Consolas", HANDLE output_handle = stdoutput() )
    {
        // nFont: (no use)
        // 14 Console
        // 15 Lucida Console
        // 6  ������
        // dwFontSize   Consolas    Lucida Console  ������
        // 10:          5,  10      6,  10          5,  11
        // 12:          6,  12      7,  12          6,  14
        // 14:          7,  14      8,  14          7,  16
        // 16:          8,  16      10, 16          8,  18
        // 18:          8,  18      11, 18          9,  21
        // 20:          9,  20      12, 20          10, 23
        // 24:          11, 24      14, 24          12, 27
        // 28:          13, 28      17, 28          14, 32
        // 36:          17, 36      22, 36          18, 41
        // FaceName:
        // Lucida Console
        // Consolas
        // Terminal
        // ������

        SetConsoleOutputCP( face_name == L"������" ? 936 : CP_UTF8 ); // DO NOT use CP_ACP
        CONSOLE_FONT_INFOEX f;
        f.cbSize = sizeof( CONSOLE_FONT_INFOEX );
        f.nFont = 0;
        f.dwFontSize.X = 0;
        f.dwFontSize.Y = font_size;
        f.FontFamily = FF_DONTCARE;
        f.FontWeight = FW_NORMAL;
        wcscpy_s( f.FaceName, face_name.c_str() );

        if ( 0 == SetCurrentConsoleFontEx( output_handle, FALSE, &f ) )
        {
            std::cout << "failed: " << GetLastError() << std::endl;
            return;
        }
    }

    static void disable_close_button()
    {   
        HWND w = GetConsoleWindow();
        HMENU m = GetSystemMenu( w, FALSE );
        DeleteMenu( m, SC_CLOSE , MF_BYCOMMAND );
        DeleteMenu( m, SC_MINIMIZE , MF_BYCOMMAND );
        DeleteMenu( m, SC_MAXIMIZE , MF_BYCOMMAND );
        DrawMenuBar( w );
    }

    static void set_color( WORD color, HANDLE output_handle = stdoutput() )
    {
        DWORD written = 0;
        COORD coord = { 0, 0 };
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo( output_handle, &csbi );
        csbi.wAttributes = color;
        SetConsoleTextAttribute( output_handle, csbi.wAttributes );
        FillConsoleOutputAttribute( output_handle, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, coord, &written ); 
    }

    static void set_window( SHORT col, SHORT row, HANDLE output_handle = stdoutput() )
    {
        COORD coord = { 0, 0 };
        COORD size = { col, row };
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo( output_handle, &csbi );

        // make sure buffer size is bigger window size
        COORD cur_size = { csbi.srWindow.Right - csbi.srWindow.Left + 1, csbi.srWindow.Bottom - csbi.srWindow.Top + 1 };
        COORD tmp_buf_size = { std::max<int>(cur_size.X, col), std::max<int>(cur_size.Y, row) };
        SetConsoleScreenBufferSize( output_handle, tmp_buf_size );

        SMALL_RECT new_window = csbi.srWindow;
        new_window.Right = new_window.Left + col - 1;
        new_window.Bottom = new_window.Top + row - 1;
        SetConsoleWindowInfo( output_handle, TRUE, &new_window );

        SetConsoleScreenBufferSize( output_handle, size );
    }

    static int WINAPI console_ctrl_handler( DWORD  dwCtrlType )
    {
        std::cout << static_cast<char>(7) << std::endl;

        switch ( dwCtrlType )
        {
        case CTRL_C_EVENT:
            std::cout << "Ctrl + C" << std::endl;
            break;
        case CTRL_BREAK_EVENT:
            std::cout << "Ctrl + BREAK" << std::endl;
            break;
        case CTRL_CLOSE_EVENT:
            std::cout << "CLOSE EVENT" << std::endl;
            break;
        case CTRL_LOGOFF_EVENT:
            std::cout << "LOGOFF EVENT" << std::endl;
            break;
        case CTRL_SHUTDOWN_EVENT:
            std::cout << "SHUTDOWN EVENT" << std::endl;
            break;
        }

        return TRUE;
    }

    static void set_console_ctrl_handler()
    {
        SetConsoleCtrlHandler( console_ctrl_handler, TRUE );
    }


    static void disable_console_mode( DWORD disable_mode )
    {
        // must call this before SetConsoleMode
        HANDLE stdinput = GetStdHandle(STD_INPUT_HANDLE);
        DWORD mode = 0;
        GetConsoleMode( stdinput, &mode );
        mode &= ~disable_mode;
        SetConsoleMode( stdinput, mode );
    }

    static void cls( HANDLE output_handle = stdoutput() )
    {
        COORD coord = { 0, 0 };
        CONSOLE_SCREEN_BUFFER_INFOEX csbi;
        csbi.cbSize = sizeof( CONSOLE_SCREEN_BUFFER_INFOEX );
        GetConsoleScreenBufferInfoEx( output_handle, &csbi );
        CHAR_INFO ch;
        ch.Attributes = csbi.wAttributes;
        ch.Char.UnicodeChar = L' ';
        SMALL_RECT wrige_region;
        WriteConsoleOutput( output_handle, &ch, csbi.dwSize, coord, &wrige_region ); 
    }
};


inline std::ostream& operator <<( std::ostream& os, const COORD& c )
{
    return os << "(" << c.X << ", " << c.Y << ")";
}

inline std::ostream& operator <<( std::ostream& os, const SMALL_RECT& s )
{
    return os << "(" << s.Left << ", " << s.Top << ", " << s.Right << ", " << s.Bottom << ")";
}

inline std::ostream& operator <<( std::ostream& os, const CONSOLE_SCREEN_BUFFER_INFO& c )
{
    return os
        << "dwSize: " << c.dwSize << std::endl
        << "dwCursorPosition: " << c.dwCursorPosition << std::endl 
        << "wAttributes: " << c.wAttributes << std::endl 
        << "srWindow: " << c.srWindow << std::endl 
        << "dwMaximumWindowSize: " << c.dwMaximumWindowSize;
}
