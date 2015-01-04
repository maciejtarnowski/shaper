#include "stdafx.h"

using namespace std;

Console::Console()
{
    this->height = 0;
    this->width = 0;
}

void Console::updateSize()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

    this->height = csbi.srWindow.Bottom - csbi.srWindow.Top  + 1;
    this->width  = csbi.srWindow.Right  - csbi.srWindow.Left + 1;
}

int Console::getWidth()
{
    return this->width;
}

int Console::getHeight()
{
    return this->height - 1; // save one row for help message
}

void Console::printChar(char character, int x, int y)
{
    this->gotoXY(x, y);
    cout << character;
}

float Console::getFontRatio()
{
    COORD fontSize = this->getFontSize();
    float ratio = (float)fontSize.Y / (float)fontSize.X;
    return (ratio < 1 ? 1 : ratio); // limit ratio to <1;Inf)
}

void Console::printHelp()
{
    this->updateSize();
    this->gotoXY(0, this->getHeight()); // go to last row

    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE); // black text on white background
    cout << "strzalki - ruch" << "\t\t" << "+ / - - zmiana rozmiaru figury" << "\t\t" << "ESC - wyjscie";
    SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // back to standard white text on black background
}

void Console::clear()
{
    system("cls"); // easiest way to clear console
}

// -- private

void Console::gotoXY(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

COORD Console::getFontSize()
{
    CONSOLE_FONT_INFO cfi;
    GetCurrentConsoleFont(GetStdHandle(STD_OUTPUT_HANDLE), false, &cfi);
    return cfi.dwFontSize;
}
