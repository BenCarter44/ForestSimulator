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
#include "Table.h"
 
 
int main(int argc, char** argv)
{
    Window::initGL(argc, argv);

    Window myWindow = Window("Hello World - Large", 800, 600);
    myWindow.setStartPos(0,0);
    myWindow.setWorldDimensions(1000,750);
    Table tableObject = Table();
    myWindow.addObject(&tableObject);

    myWindow.launch();

    myWindow.mainLoop();
    return 0;
}
    