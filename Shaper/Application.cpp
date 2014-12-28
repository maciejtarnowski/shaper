#include "stdafx.h"

using namespace std;

// application constructor, initializes app
Application::Application()
{
    console.updateSize();
    this->selectedChar = this->askForCharToDraw();
    this->shape.setInitialSize(this->askForInitialSize());
    this->shape.setCharacter(this->selectedChar);

    console.clear();

    this->renderShape(); // initial render
    this->console.printHelp(); // print bottom help row
}

void Application::run()
{
    while (true) {
        if (!this->handleKeyPress(_getch())) {
            break; // false from handleKeyPress stops the app
        }

        console.clear();

        this->renderShape(); // initial render of the shape
        this->console.printHelp(); // initial help print
    }
}

// -- private

bool Application::handleKeyPress(char key)
{
    // see remark http://msdn.microsoft.com/en-us/library/078sfkak.aspx
    if (key == 0 || key == 0xE0) {
        key = _getch();
    }

    switch (key) {
        case DOWN:
            this->shape.move(0, 1); // (0, 0) is top-left corner of the screen, so going down equals incrementing Y coord
            break;
        case UP:
            this->shape.move(0, -1);
            break;
        case LEFT:
            this->shape.move(-1, 0);
            break;
        case RIGHT:
            this->shape.move(1, 0);
            break;
        case PLUS:
            this->shape.resize(1); // add 1 to size
            break;
        case MINUS:
            this->shape.resize(-1); // substract 1 from size
            break;
        case ESC:
            return false; // false means stop the app
        default:
            break;
    }

    return true; // true means continue execution
}

char Application::askForCharToDraw()
{
    console.clear();
    char selectedChar = Shape::DEFAULT_CHAR; // set to shape's default
    cout << "Podaj znak do narysowania figury: ";
    cin >> selectedChar;
    cin.clear(); // clear cin buffer so it is empty before another read
    cin.ignore(INT_MAX, '\n'); // see http://stackoverflow.com/questions/5131647/why-would-we-call-cin-clear-and-cin-ignore-after-reading-input
    return selectedChar;
}

int Application::askForInitialSize()
{
    int selectedSize;
    while (true) {
        console.clear();
        selectedSize = Shape::DEFAULT_SIZE; // reset value to shape's default
        cout << "Podaj poczatkowy rozmiar figury (" << Shape::MIN_SIZE << " - " << Shape::MAX_SIZE << ") [" << selectedSize << "]: ";
        cin >> selectedSize;
        if (selectedSize >= Shape::MIN_SIZE && selectedSize <= Shape::MAX_SIZE) { // check whether provided size is within accepted range
            break;
        }
    }
    return selectedSize;
}

// handy helper to render the shape
void Application::renderShape()
{
    this->shape.render();
}
