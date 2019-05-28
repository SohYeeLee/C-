/*
 * WinConsole.cpp
 * @version: 1.080822
 * @author: Ban Kar Weng (William)
 * @date: 22 August 2008
 * @email: kwban@mmu.edu.my
 *
 * Description:
 *      This file contains the function definition
 *      for the function declarations in WinConsole.hpp.
 *
 * Notice:
 *      These functions are not fully tested and
 *      the author did them in a hurry. Hence,
 *      use them at your own risk!
 *
 *      You are free to modify the codes here for your
 *      own purposes or for improvements.
 */

#include "WinConsole.hpp"

/* Console Color */
static MyColor foreground = WHITE;
static MyColor background = BLACK;

/* Console Window */
static int width = 1;
static int height = 1;

/* Some Low Level Console Structures */
static HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
static COORD largestWindow = GetLargestConsoleWindowSize(hOut);

/* 
 * Set the title for Console Window
 */
void setConsoleTitle(const string& title)
{
    if ( !SetConsoleTitle( title.c_str() ) )
    {
        cerr << "In \'setConsoleTitle()\':"
             << "- Error calling <SetConsoleTitle>" << endl;
    }
}

/* 
 * Set the size for Console Window
 *
 * @width: width of the window ( < 128 )
 * @height: height of the window ( < 59 )
 */
void setConsoleSize(int width, int height)
{
    CONSOLE_SCREEN_BUFFER_INFO screen_info;
    
    // get console screen buffer to obtain maximum window size
    if ( !GetConsoleScreenBufferInfo(hOut, &screen_info) )
    {
        cerr << "In \'setConsoleSize()\':"
             << "- Error calling <GetConsoleScreenBufferInfo>" << endl;
        cerr << "Aborting Function!" << endl;

        return;
    }

    // validate width and height 
    if (width < 1)
        width = 1;
    if (height < 1)
        height = 1;
    
    if (width > largestWindow.X)
        width = largestWindow.X;
    if (height > largestWindow.Y)
        height = largestWindow.Y;

    SMALL_RECT window_rect = {0, 0, 0, 0};
    
    // make window size smallest possible first
    if ( !SetConsoleWindowInfo(hOut, TRUE, &window_rect) )
    {
        cerr << "In \'setConsoleSize()\':"
             << "- Error at <SetConsoleWindowInfo>" << endl;
        cerr << "Aborting Function!" << endl;
        return;
    }
    
    // change screen buffer size
    if ( !SetConsoleScreenBufferSize(hOut, (COORD){width, height}) )
    {
        cerr << "In \'setConsoleSize()\':"
             << "- Error calling <SetConsoleScreenBufferSize>" << endl;
        cerr << "Aborting Function!" << endl;

        return;
    }
    
    window_rect.Right   = width - 1;
    window_rect.Bottom  = height - 1;

    // change console window size to the requested size
    if ( !SetConsoleWindowInfo(hOut, TRUE, &window_rect) )
    {
        cerr << "In \'setConsoleSize()\':"
             << "- Error calling <SetConsoleWindowInfo>" << endl;
        cerr << "Aborting Function!" << endl;

        return;
    }

    // assign width and height
    ::width = width;
    ::height = height;
}

/*
 * Set Console display mode to fullscreen or windowed mode.
 */
void setConsoleFullscreen(const bool& fullscreen)
{
    COORD dummy;

    // Fullscreen mode selected
    if (fullscreen)
    {
        if ( !SetConsoleDisplayMode(hOut, CONSOLE_FULLSCREEN_MODE, &dummy) )
        {
            cerr << "In \'setConsoleFullscreen()\':"
                 << "- Fullscreen Mode Failed!" << endl;
        }
    }
    // Windowed Mode selected
    else
    {
        if ( !SetConsoleDisplayMode(hOut, CONSOLE_WINDOWED_MODE, &dummy) )
        {
            cerr << "In \'setConsoleFullscreen()\':"
                 << "- Windowed Mode Failed! " << endl;
        }
    }

}

/*
 * Set current background color
 *
 * @color: color for background (16 choices from WinConsole.hpp)
 */
void setBackgroundColor(const MyColor& color)
{
    background = color;
    SetConsoleTextAttribute(hOut, foreground + (background << 4) );
}

/*
 * Set current foreground color
 *
 * @color: color for foreground (16 choices from WinConsole.hpp)
 */
void setForegroundColor(const MyColor& color)
{
    foreground = color;
    SetConsoleTextAttribute(hOut, foreground + (background << 4) );
}

/*
 * Change current cursor position
 *
 * @x: x-value (increases from left to right)
 * @y: y-value (increase from top to bottom)
 */
void setCursorPosition(int x, int y)
{
    COORD cursor_pos;

    cursor_pos.X = x;
    cursor_pos.Y = y;

    if ( !SetConsoleCursorPosition(hOut, cursor_pos) )
        cerr << "In \'setCursorPosition()\':"
             << "- Error calling <SetConsoleCursorPosition>" << endl;
}

/*
 * Set Cursor's visibility
 *
 * @isVisible: 'true' for visible
 *             'false' for invisible
 */
void setCursorVisible(const bool& isVisible)
{
    CONSOLE_CURSOR_INFO cursor_info;

    // get cursor info
    GetConsoleCursorInfo(hOut, &cursor_info);

    // set cursor visibility based on the parameter
    cursor_info.bVisible = static_cast<BOOL>(isVisible);

    // set the cursor
    SetConsoleCursorInfo(hOut, &cursor_info);
}

/*
 * Set Cursor's percentage of fill.
 *
 * Description:
 *      The higher the percentage, the bigger the cursor.
 *
 * @percentage: between 1 to 100
 *
 */
void setCursorFill(int percentage)
{
    CONSOLE_CURSOR_INFO cursor_info;

    // get cursor info
    GetConsoleCursorInfo(hOut, &cursor_info);

    if (percentage < 1)
        percentage = 1;
    else if (percentage > 100)
        percentage = 100;

    // set cursor visibility based on the parameter
    cursor_info.dwSize = static_cast<DWORD>(percentage);

    // set the cursor
    SetConsoleCursorInfo(hOut, &cursor_info);
}
