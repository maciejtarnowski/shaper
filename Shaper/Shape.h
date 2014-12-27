#pragma once

class Shape
{
    char character;

    int currentPosX,
        currentPosY,
        size;

    Console console;

public:
    static int const MIN_SIZE = 1,
                     MAX_SIZE = 15;

    Shape();
    Shape(char character);
    void render();
    void setCharacter(char character);
    void move(int deltaX, int deltaY);
    void resize(int delta);
    void setInitialSize(int size);
private:
    bool willCollide(int deltaX, int deltaY, int deltaSize);
    int getHeight();
    int getWidth();
    void setDefaultAttributes();
};