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
#include "Cup1.h"
#include "Cup2.h"
#include "Cup3.h"
#include "Cup4.h"
#include "stickyNotes.h"
#include "GreenPen.h"
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
    

    stickyNotes stickyNotesObeject = stickyNotes();
    myWindow.addObject(&stickyNotesObeject);

    GreenPen penG = GreenPen();
    myWindow.addObject(&penG);

    Cup2 cup2 = Cup2();
    myWindow.addObject(&cup2);

    Cup3 cup3 = Cup3();
    myWindow.addObject(&cup3);


    Cup1 cup1 = Cup1();
    myWindow.addObject(&cup1);

    Cup4 cup4 = Cup4();
    myWindow.addObject(&cup4);
    
    BlackPen penB = BlackPen();
    myWindow.addObject(&penB);


    Table tableObject = Table();
    myWindow.addObject(&tableObject);

    
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
    
