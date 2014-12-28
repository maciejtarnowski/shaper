#pragma once

class Application
{
    char selectedChar;

    Console console;

    // ASCII codes of keys returned by _getch
    enum Keys {
        UP    = 72,
        DOWN  = 80,
        LEFT  = 75,
        RIGHT = 77,
        PLUS  = 43,
        MINUS = 45,
        ESC   = 27
    };

    Shape shape;

public:
    Application();
    void run();

private:
    bool handleKeyPress(char key);
    char askForCharToDraw();
    int askForInitialSize();
    void renderShape();
};
