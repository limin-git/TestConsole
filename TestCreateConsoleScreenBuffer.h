#pragma once


class TestCreateConsoleScreenBuffer
{
public:

    TestCreateConsoleScreenBuffer();
    ~TestCreateConsoleScreenBuffer();

    void create_buffer();
    void get_new_buffer_info();

public:

    HANDLE m_std_output_handle;
    UINT m_cp;
    UINT m_output_cp;
};
