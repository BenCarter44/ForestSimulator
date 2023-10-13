/**
 * @file Wall.cpp
 * @author Benjamin Carter, Josh Canode.
 * @brief Creates the Wall object using the multiPolygon class.
 * @version 0.1
 * @date 2023-10-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "Wall.h"

#ifndef PI
#define PI           3.14159265358979323846  /* pi */
#endif

Wall::Wall()
{
    wallTexture = Texture("wall.png",1024);
}
void Wall::postWindowCreate()
{
    wallTexture.setupTexture();
}
void Wall::draw()
{
    glColor3f(202.0f / 255.0f, 192.0f / 255.0f, 182.0f / 255.0f);
    wallTexture.start();
    glBegin(GL_POLYGON);
        wallTexture.markCoord(0,0);
        glVertex2f(0,0);
        wallTexture.markCoord(1024,0);
        glVertex2f(1000,0);
        wallTexture.markCoord(1024,1024);
        glVertex2f(1000,750);
        wallTexture.markCoord(0,1024);
        glVertex2f(0,750);
    glEnd();
    wallTexture.stop();

}