/**
 * @file Window.cpp
 * @author Benjamin Carter and Josh Canode
 * @brief The Window cpp file.
 * @version 0.1
 * @date 2023-09-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "Window.h"

int Window::sizeX = 0;
int Window::sizeY = 0;
int Window::startX = 0;
int Window::startY = 0;
const char* Window::title = "";
vector<DisplayObject*> Window::allObjects = vector<DisplayObject*>();

// this is a static function.
void Window::initGL(int &argc, char** argv)
{
    DEBUG_WIN(glutInit(&argc, argv));
    glutInit(&argc, argv);
    DEBUG_WIN(glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH););
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
}

Window::Window()
{
    Window::sizeX = 100;
    Window::sizeY = 100;
    Window::startX = 0;
    Window::startY = 0;
    Window::title = "A window created";
}

Window::Window(const char* titl)
{
    Window::sizeX = 100;
    Window::sizeY = 100;
    Window::startX = 0;
    Window::startY = 0;
    Window::title = titl;
}

Window::Window(const char* title, int inX, int inY)
{
    Window::sizeX = inX;
    Window::sizeY = inY;
    Window::startX = 0;
    Window::startY = 0;
    Window::title = title;
}

Window::Window(int inX, int inY)
{
    Window::sizeX = inX;
    Window::sizeY = inY;
    Window::startX = 0;
    Window::startY = 0;
    Window::title = "A window created";
}


void Window::launch()
{
    DEBUG_WIN( glutInitWindowSize(Window::sizeX, Window::sizeY));
    glutInitWindowSize(Window::sizeX, Window::sizeY);

    DEBUG_WIN(glutInitWindowPosition(startX, startY));
    glutInitWindowPosition(Window::startX, Window::startY);

    DEBUG_WIN(glutCreateWindow(title));
    glutCreateWindow(Window::title);

    DEBUG_WIN(glutDisplayFunc(Window::mainDisplay));
    glutDisplayFunc(Window::mainDisplay);

     // basically. do 3D.  https://registry.khronos.org/OpenGL-Refpages/gl4/html/glEnable.xhtml
    DEBUG_WIN(glEnable(GL_DEPTH_TEST));
    glEnable(GL_DEPTH_TEST);
    
}

// this is a static function.
void Window::mainDisplay()
{
    for(int x = 0; x < allObjects.size(); x++)
    {
        allObjects[x]->draw();
    }
}

void Window::addObject(DisplayObject* disp)
{
    allObjects.push_back(disp);
}

void Window::mainLoop()
{
    DEBUG_WIN(glutMainLoop());
    glutMainLoop();
} 

int Window::getSizeX()
{
    return Window::sizeX;
}

int Window::getSizeY()
{
    return Window::sizeY;
}
void Window::setStartPos(int x, int y)
{
    Window::startX = x;
    Window::startY = y;
}

const char* Window::getTitle()
{
    return Window::title;
}