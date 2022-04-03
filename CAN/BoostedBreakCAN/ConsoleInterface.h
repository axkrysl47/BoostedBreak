/***
 *  BoostedBreak - BoostedBreakCAN Program
 *
 *  ConsoleInterface.h
 *
 *  Author: Alexander Krysl (axkrysl47)
 *  Date:   2022/04/03
 **/

#pragma once
#include <string>
#include <iostream>
#include <conio.h>
#include <atlstr.h>

#ifndef __CONSOLEINTERFACEH__
#define __CONSOLEINTERFACEH__

//static HANDLE hConsole;

static void ConsoleInit()
{
    //hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
}

static void ConsoleClear()
{
    system("cls");
}

static void ConsolePause()
{
    system("PAUSE");
}

static void ConsolePrint(std::string str)
{
    std::cout << str;
}

static void ConsolePrint(std::string str, int16_t xpos)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO cbsi;
    COORD pos;
    
    if (GetConsoleScreenBufferInfo(hConsole, &cbsi))
    {
        pos = { xpos , cbsi.dwCursorPosition.Y };
    }
    else
    {
        pos = { xpos, 0 };
    }
    SetConsoleCursorPosition(hConsole, pos);

    std::cout << str;
}

static void ConsolePrint(std::string str, int16_t xpos, int16_t ypos)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = { xpos, ypos };

    SetConsoleCursorPosition(hConsole, pos);

    std::cout << str;
}

static void ConsoleCursor(int16_t xpos, int16_t ypos)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = { xpos, ypos };

    SetConsoleCursorPosition(hConsole, pos);
}

static char ConsoleInput()
{
    return _getch();
}

static void DebugConsolePrint(std::string str)
{
    std::cout << str;
}

static char DebugConsoleInput()
{
    return _getch();
}

#endif //__CONSOLEINTERFACEH__