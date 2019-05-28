/*
 * WinConsole.hpp
 * @version: 1.080822
 * @author: Ban Kar Weng (William)
 * @date: 22 August 2008
 * @email: kwban@mmu.edu.my
 *
 * Description:
 *      This file contains a set of functions that
 *      changes the properties of Windows Console a.k.a.
 *      Command Prompt. These functions generally
 *      wraps the Windows Console functions so that it's
 *      easier to understand and use.
 *
 * Notice:
 *      This file is only tested in Windows XP, so it is
 *      not guaranteed to work in Windows Vista. Moreover,
 *      the author creates this file in a hurry. Hence,
 *      use this at your own risk!
 *
 *      You are free to modify the codes here for your
 *      own purposes or for improvements.
 */

#ifndef WIN_CONSOLE_H
#define WIN_CONSOLE_H

// illegally change OS version for fullscreen to work.
#undef _WIN32_WINNT
#define _WIN32_WINNT 0x0501
// include Windows Console functions.
#include <windows.h>

#include <iostream>
using namespace std;

// Color Constants
enum MyColor
{
    BLACK,
    DARKBLUE,
    DARKGREEN,
    TEAL,
    MAROON,
    PURPLE,
    OLIVE,
    LIGHTGRAY,
    DARKGRAY,
    BLUE,
    GREEN,
    CYAN,
    RED,
    PINK,
    YELLOW,
    WHITE
};

/* Console Window Functions */
void setConsoleTitle(const string& title);
void setConsoleSize(int width, int height);
void setConsoleFullscreen(const bool& fullscreen);

/* Console Color Functions */
void setBackgroundColor(const MyColor& color);
void setForegroundColor(const MyColor& color);

/* Console Cursor Properties */
void setCursorPosition(int x, int y);
void setCursorVisible(const bool& isVisible);
void setCursorFill(int percentage);

#endif
