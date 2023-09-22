/**
 * @file DisplayObject.h
 * @author your name (you@domain.com)
 * @brief This file contains the DisplayObject class, a "super class" for other objects.
 * @version 0.1
 * @date 2023-09-22
 * 
 * @copyright Copyright (c) 2023
 * 
 * 
 * Other objects will inherit this class and override the draw() function.
 * 
 * When designing other objects.... 
 * Make a class in C++ that inherits this class, but overriding the draw() function. 
 * Inside you can use whatever OpenGL stuff you want. 
 * 
 * You can call DEBUG_DISP() if you want to add the command to cout for debugging.
 * Only active if DEBUG_DISP_CMD is defined. You will want to change 
 * DEBUG_DISP_CMD to a custom one per obejct. Eg. DEBUG_ORANGE_CMD for the orange object.
 * 
*/
#ifndef DISPLAY_OBJECT_H
#define DISPLAY_OBJECT_H

/* the glut library */
#include <GL/glut.h>


/* DEFINE DEBUG_GLUT_CMD to get cout's of the glut commands to console. */
// #define DEBUG_DISP_CMD

#ifdef DEBUG_DISP_CMD
#define DEBUG_DISP(ARG) (cout << #ARG";\n")
#include <iostream>
#else
#define DEBUG_DISP(ARG) while(false)
#endif


using namespace std;

class DisplayObject
{
public:
    /**
     * @brief draw the object onto the screen.
    */
    virtual void draw();
};

#endif
