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
    TextWriter(void* font, int screenWidth, int screenHeight);
    void write(float x, float y, const char* string);
    
    void close();
   
};
#endif