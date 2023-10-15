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

    // shadow of table first
   // glColor3f(CC(111), CC(100), CC(78));
    glColor3f(CC(140), CC(129), CC(104));
  // glColor3f(CC(202), CC(192), CC(182));
    wallTexture.start();
    glBegin(GL_POLYGON);
        wallTexture.markCoord(Window::mapValue(200,0,1000,1024,0),Window::mapValue(630,750,0,1024,0));
        glVertex2f(203,630);
        wallTexture.markCoord(Window::mapValue(200,0,1000,1024,0),1024);
        glVertex2f(200,750);
        wallTexture.markCoord(Window::mapValue(782,0,1000,1024,0),1024);
        glVertex2f(782,750);
        wallTexture.markCoord(Window::mapValue(694,0,1000,1024,0),Window::mapValue(570,750,0,1024,0));
        glVertex2f(694,570);
    glEnd();
    wallTexture.stop();

    // WALL
  //  glColor3f(CC(202), CC(192), CC(182));
    glColor3f(CC(230), CC(225), CC(221));
    wallTexture.start();
    glBegin(GL_POLYGON);
        wallTexture.markCoord(1024,1024);
        glVertex2f(0,0);
        wallTexture.markCoord(0,1024);
        glVertex2f(1000,0);
        wallTexture.markCoord(0,0);
        glVertex2f(1000,750);
        wallTexture.markCoord(1024,0);
        glVertex2f(0,750);
    glEnd();
    wallTexture.stop();

}