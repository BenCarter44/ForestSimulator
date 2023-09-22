/**
 * @file main.cpp
 * @author Benjamin Carter, Josh Canode.
 * @brief The main program.
 * @version 0.1
 * @date 2023-09-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <GL/glut.h>
#include "Window.h"
#include "DisplayObject.h"
 
 
int main(int argc, char** argv)
{
    Window::initGL(argc, argv);

    Window myWindow = Window("Hello World - Large", 400, 300);
    myWindow.setStartPos(100,200);
    DisplayObject dummyObject = DisplayObject();
    myWindow.addObject(&dummyObject);

    myWindow.launch();

    myWindow.mainLoop();
    return 0;
}
    