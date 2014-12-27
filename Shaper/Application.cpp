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
    char selectedChar = '&';
    cout << "Podaj znak do narysowania figury: ";
    cin >> selectedChar;
    return selectedChar;
}

int Application::askForInitialSize()
{
    console.clear();
    int selectedSize = 1; // default value is 1
    cout << "Podaj poczatkowy rozmiar figury (" << Shape::MIN_SIZE << " - " << Shape::MAX_SIZE << ") [1]: ";
    cin >> selectedSize;
    if (selectedSize >= Shape::MIN_SIZE && selectedSize <= Shape::MAX_SIZE) { // check whether provided size is within accepted range
        return selectedSize;
    } else {
        return 1; // otherwise return 1
    }
}

// handy helper to render the shape
void Application::renderShape()
{
    this->shape.render();
}
