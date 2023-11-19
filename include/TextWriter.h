/**
 * @file TextWriter.h
 * @author Benjamin Carter and Josh Canode
 * @brief This holds the Text Writer Definitions.
 * @version 1.0
 * @date 2023-11-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef TEXT_WRITER_H
#define TEXT_WRITER_H

#include <GL/glut.h>
#include "Mesh.h"

/**
 * @brief The StringDraw class. Draws a string to a window.
 * 
 */
class TextWriter
{
private:
     /**
     * @brief Helper for rendering strings to window.
     * 
     * @param x 
     * @param y 
     * @param font - Use GLUT fonts.
     * @param string 
     */
    void renderBitmapString(float x, float y, void *font, const char* string);

    void* ft;
    int screenWidth;
    int screenHeight;

public:
    /**
     * @brief Construct a Text Writer object.
     * 
     * @param font - The font to use. Use GLUT fonts.
     * @param screenWidth  - The screen width
     * @param screenHeight - The screen height
     */
    TextWriter(void* font, int screenWidth, int screenHeight);

    /**
     * @brief Write the string onto the screen at given point. Point is in normalized -1.0 to 1.0 coordinates, with center being 0,0
     * 
     * @param x 
     * @param y 
     * @param string 
     */
    void write(float x, float y, const char* string);
    
    /**
     * @brief Reset and cleanup after glut operations.
     * 
     */
    void close();
   
};
#endif