#include "Window.h"

Window::Window()
{
    title = "A window created";
    sizeX = 100;
    sizeY = 100;
}

Window::Window(const char* titl)
{
    title = titl;
}

Window::Window(const char* title, int inX, int inY)
{
    this->title = title;
    sizeX = inX;
    sizeY = inY;
}

Window::Window(int inX, int inY)
{
    title = "A window created";
    sizeX = inX;
    sizeY = inY;
}

void Window::setStartX(int x)
{
    startX = x;
}
void Window::setStartY(int y)
{
    startY = y;
}

int Window::getSizeX()
{
    return sizeX;
}

int Window::getSizeY()
{
    return sizeY;
}
int Window::getStartX()
{
    return startX;
}
int Window::getStartY()
{
    return startY;
}

const char* Window::getTitle()
{
    return title;
}

void Window::display()
{
    for(int x = 0; x < allObjects.size(); x)
    {
        allObjects[x]->draw();
    }
}