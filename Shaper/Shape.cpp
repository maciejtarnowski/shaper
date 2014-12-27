#include "stdafx.h"

using namespace std;

Shape::Shape(char character) : character(character) {}

Shape::Shape() : character('&') {}

void Shape::render()
{
    Console console;
    int posX = this->currentPosX,
        posY = this->currentPosY;
    int upper = 0, middle = 0, lower = 0;
    for (upper = 0; upper < size; upper++) {
        console.printChar(this->character, posX + upper, posY + upper); // go 1 down and 1 right in each iteration
    }
    for (middle = 0; middle <= (size * console.getFontRatio()); middle++) {
        console.printChar(this->character, posX + upper + middle, posY + upper);
    }
    for (lower = 0; lower < size; lower++) {
        console.printChar(this->character, posX + upper - 1 - lower, posY + upper + 1 + lower);
    }
    return;
}

void Shape::setCharacter(char character)
{
    this->character = character;
}

// move shape by vector
void Shape::move(int deltaX, int deltaY)
{
    if (!this->willCollide(deltaX, deltaY, 0)) {
        this->currentPosX += deltaX;
        this->currentPosY += deltaY;
    }
}

void Shape::resize(int delta)
{
    if (this->size + delta < 1 || this->size + delta > 15) {
        return;
    }
    if (!this->willCollide(0, 0, delta)) {
        this->size += delta;
    }
}

bool Shape::willCollide(int deltaX, int deltaY, int deltaSize)
{
    Console console;
    console.updateSize();

    int height = (this->size + deltaSize) * 2 + 1,
        width  = (this->size + deltaSize) + 1 + (this->size + deltaSize) * console.getFontRatio();

    if (this->currentPosX + deltaX < 0 || this->currentPosY + deltaY < 0) {
        return true;
    }

    return !(console.getHeight() >= this->currentPosY + deltaY + height && console.getWidth() >= this->currentPosX + deltaX + width);
}

void Shape::setInitialAttributes(int x, int y, int size)
{
    this->currentPosX = x;
    this->currentPosY = y;
    this->size        = size;
}
