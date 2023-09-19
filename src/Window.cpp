#include "Window.h"

Window::Window()
{

}

Window::Window(const char[] titl)
{

}

Window::Window(const char[] title, int inX, int inY)
{
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