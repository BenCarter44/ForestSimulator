/**
 * @file Orange.cpp
 * @author Benjamin Carter, Josh Canode.
 * @brief Creates the orange object using the multiPolygon class.
 * @version 0.1
 * @date 2023-10-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "Orange.h"

#ifndef PI
#define PI           3.14159265358979323846  /* pi */
#endif

Orange::Orange()
{
    orangeTexture = Texture("orange.png", 256);
}

void Orange::postWindowCreate()
{
    orangeTexture.setupTexture();
}


void Orange::draw()
{
    glColor3f(CC(248),CC(208),CC(173));

    // then is verticies

    Point orangePoints[] = {
        {488,249},
        {478,250},
        {469,252},
        {461,256},
        {455,262},
        {450,267},
        {446,275},
        {445,282},
        {444,291},
        {443,301},
        {445,311},
        {449,323},
        {459,333},
        {467,333},
        {508,334},
        {512,330},
        {517,325},
        {522,317},
        {526,309},
        {528,298},
        {528,284},
        {524,274},
        {518,263},
        {511,257},
        {502,252},
        {492,250},
        {484,262}
    };

    orangeTexture.start();
    glBegin(GL_TRIANGLE_FAN);
    for(int i = 0; i < 27; i++)
    {
        orangeTexture.markCoord(Window::mapValue(orangePoints[i].x,443,528, 28, 224), Window::mapValue(orangePoints[i].y,417, 248.3, 13, 228));
        glVertex2f(orangePoints[i].x,orangePoints[i].y);
    }
    glEnd();
    orangeTexture.stop();



    glFlush();
}