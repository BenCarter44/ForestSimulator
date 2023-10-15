/**
 * @file glIncludes.h
 * @author Benjamin Carter and Josh Canode
 * @brief Includes all GLUT/GL and other libraries in the correct order.
 * @version 0.1
 * @date 2023-10-14
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef INCLUDED_GL_STUFF
#define INCLUDED_GL_STUFF
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GLUT
#include <GL/glut.h>

#endif