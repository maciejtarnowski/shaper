#pragma once

class Shape
{
// -- private
    char character;

    int currentPosX,
        currentPosY,
        size;

    Console console;

public:
    static int const MIN_SIZE     = 1,
                     MAX_SIZE     = 15,
                     DEFAULT_SIZE = 1;

    static char const DEFAULT_CHAR = '&';

    Shape();
    Shape(char character);
    void render();
    void setCharacter(char character);
    void move(int deltaX, int deltaY);
    void resize(int delta);
    void setInitialSize(int size);
private:
    bool willCollide(int deltaX, int deltaY, int deltaSize);
    int getHeight(int deltaSize = 0);
    int getWidth(int deltaSize = 0);
    void setDefaultAttributes();
};
