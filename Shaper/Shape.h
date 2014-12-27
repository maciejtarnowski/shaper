#pragma once

class Shape
{
    char character;

    int currentPosX,
        currentPosY,
        size;

public:
    Shape();
    Shape(char character);
    void render();
    void setCharacter(char character);
    void move(int deltaX, int deltaY);
    void resize(int delta);
    void setInitialAttributes(int x, int y, int size);
private:
    bool willCollide(int deltaX, int deltaY, int deltaSize);
};