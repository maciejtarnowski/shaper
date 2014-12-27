#pragma once

class Console
{
    int width,
        height;

public:
    Console();
    void updateSize();
    int getWidth();
    int getHeight();
    void printChar(char character, int x, int y);
    COORD getFontSize();
    float getFontRatio();
    void printHelp();

private:
    void gotoXY(int x, int y);
};