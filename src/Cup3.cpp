/**
 * @file Cup3.cpp
 * @author Benjamin Carter, Josh Canode.
 * @brief Creates a cup 3 object using the multiPolygon class.
 * @version 0.1
 * @date 2023-10-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#include "Cup3.h"

#ifndef PI
#define PI           3.14159265358979323846  /* pi */
#endif

Cup3::Cup3()
{
    cupTexture = Texture("cup3.png", 512);
}

void Cup3::postWindowCreate()
{
    cupTexture.setupTexture();
}

void Cup3::draw()
{
    // Create a "circle" face. More like a 20 sided polygon.

        glColor3f(CC(223), CC(217), CC(217));
    // then is verticies

    cupTexture.start();
    glBegin(GL_POLYGON);
        
        Point center = {659, 331};
        double radiusX = 34;
        double radiusY = 1;

        int precision = 5;
        // double

        for(int r = 0; r > -180; r -= precision) // Half a circle, the top (y is flipped.)
        {
            double rad = (PI * r) / 180.0;
            float x = center.x + radiusX * cos(rad);
            float y = center.y + radiusY * sin(rad);

            cupTexture.markCoord(Window::mapValue(x,605,723,107,439),Window::mapValue(y,453,313,74,466));
            glVertex2f(x,y);
        }
        
        radiusX = 40;
        radiusY = 14;
        center = {669, 452};
        
        
        for(int r = 180; r > 0; r -= precision) // Half a circle, the top (y is flipped.)
        {
            double rad = (PI * r) / 180.0;
            float x = center.x + radiusX * cos(rad);
            float y = center.y + radiusY * sin(rad);

            cupTexture.markCoord(Window::mapValue(x,605,723,107,439),Window::mapValue(y,453,313,74,466));
            glVertex2f(x,y);
        }

    glEnd();
    cupTexture.stop();


    glFlush();
}