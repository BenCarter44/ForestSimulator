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
#include "BlackPen.h"
#include "Orange.h"
#include "CatchPhrase.h"
#include "Test.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <iostream>
 
int main(int argc, char** argv)
{
    Window::initGL(argc, argv);

    Window myWindow = Window("Hello World - Large", 800, 600);
    myWindow.setStartPos(0,0);
    myWindow.setWorldDimensions(1000,750);
    
    Test tester = Test();
    myWindow.addObject(&tester);

    BlackPen penB = BlackPen();
    myWindow.addObject(&penB);
    

    CatchPhrase cp = CatchPhrase();
    myWindow.addObject(&cp);

    Table tableObject = Table();
    myWindow.addObject(&tableObject);

    Orange orange = Orange();
    myWindow.addObject(&orange);

    myWindow.launch();

    /* GLM TEST */
    glm::vec4 vecA = glm::vec4(1.0f, 0.0f, 1.0f, 1.0f);
    glm::vec4 vecB = glm::vec4(1.0f, 0.0f, 1.0f, 1.0f);
    
    // glm::mat4 trans;
    // trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
    vecA = vecA + vecB;
    std::cout << vecA.x << ' ' << vecA.y << ' ' << vecA.z << std::endl;


    myWindow.mainLoop();
    return 0;
}
    
