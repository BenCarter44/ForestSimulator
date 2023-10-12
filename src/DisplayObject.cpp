/**
 * @file DisplayObject.cpp
 * @author Benjamin Carter And Josh Canode
 * @brief The DisplayObject cpp file.
 * @version 0.1
 * @date 2023-09-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "DisplayObject.h"



void DisplayObject::draw()
{
    DEBUG_DISP(glClear(GL_COLOR_BUFFER_BIT));
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    DEBUG_DISP(glBegin(GL_POLYGON));
    glBegin(GL_POLYGON);
        DEBUG_DISP(glVertex3f(0.5, 0.0, 0.5));
        glVertex3f(0.5, 0.0, 0.5);
        DEBUG_DISP(glVertex3f(0.5, 0.0, 0.0));
        glVertex3f(0.5, 0.0, 0.0);
        DEBUG_DISP(glVertex3f(0.0, 0.5, 0.0));
        glVertex3f(0.0, 0.5, 0.0);
        DEBUG_DISP(glVertex3f(0.0, 0.0, 0.5));
        glVertex3f(0.0, 0.0, 0.5);
    DEBUG_DISP(glEnd());
    glEnd();
    DEBUG_DISP(glFlush());
    glFlush();
    return;
}

void DisplayObject::postWindowCreate()
{
    // nothing. Put textures and what not here.
}