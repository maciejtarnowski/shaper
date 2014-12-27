#include "stdafx.h"

// default constructor
Shape::Shape() : character('&') {
    this->setDefaultAttributes();
}

// constructor with initial character
Shape::Shape(char character) : character(character) {
    this->setDefaultAttributes();
}

void Shape::render()
{
    int posX = this->currentPosX,
        posY = this->currentPosY;

    int upper = 0, middle = 0, lower = 0; // initialize variables here to be able to access them outside loops

    for (upper = 0; upper < size; upper++) {
        console.printChar(this->character, posX + upper, posY + upper); // upper arm, go 1 down and 1 right in each iteration
    }
    for (middle = 0; middle <= (size * console.getFontRatio()); middle++) {
        console.printChar(this->character, posX + upper + middle, posY + upper); // horizontal bar
    }
    for (lower = 0; lower < size; lower++) {
        console.printChar(this->character, posX + upper - 1 - lower, posY + upper + 1 + lower); // lower arm, go 1 down and 1 left in each iteration
    }
}

void Shape::setCharacter(char character)
{
    this->character = character;
}

// move shape by vector
void Shape::move(int deltaX, int deltaY)
{
    if (!this->willCollide(deltaX, deltaY, 0)) { // predict collision
        this->currentPosX += deltaX;
        this->currentPosY += deltaY;
    }
}

void Shape::resize(int delta)
{
    if (this->size + delta < Shape::MIN_SIZE || this->size + delta > Shape::MAX_SIZE) { // check whether size is within accepted range
        return;
    }
    if (!this->willCollide(0, 0, delta)) { // predict collision
        this->size += delta;
    }
}

void Shape::setInitialSize(int size)
{
    console.updateSize();
    this->size        = size;
    this->currentPosX = 0;
    this->currentPosY = console.getHeight() - (this->size * 2) - 1;
}

// -- private

// predict collision after move or resize
bool Shape::willCollide(int deltaX, int deltaY, int deltaSize)
{
    console.updateSize();

    int height = (this->size + deltaSize) * 2 + 1, // two arms
        width  = (this->size + deltaSize) + 1 + (this->size + deltaSize) * console.getFontRatio();

    if (this->currentPosX + deltaX < 0 || this->currentPosY + deltaY < 0) {
        return true; // report collision behind top-left corner of the screen
    }

    // it collides if: console height is less then current Y possition + shape height + delta Y OR console width is less then current X possition + shape width + delta X
    return console.getHeight() < this->currentPosY + deltaY + height || console.getWidth() < this->currentPosX + deltaX + width;
}

int Shape::getHeight()
{
    return this->size * 2 + 1; // two arms of size height + horizontal bar
}

int Shape::getWidth()
{
    return this->size + 1 + (this->size * console.getFontRatio()); // horizontal bar's length depends on font height/width ratio
}

void Shape::setDefaultAttributes()
{
    this->currentPosX = 0;
    this->currentPosY = 0;
    this->size        = 1;
}
