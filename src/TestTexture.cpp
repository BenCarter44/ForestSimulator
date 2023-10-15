/**
 * @file TestTexture.cpp
 * @author Benjamin Carter and Josh Canode
 * @brief The source file for the texture test class.
 * @version 0.1
 * @date 2023-10-14
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "TestTexture.h"

TestTexture::TestTexture()
{
    myTexture = Texture("wood.png", 1024);
}

void TestTexture::postWindowCreate()
{
    myTexture.setupTexture();
}

void TestTexture::draw()
{
    glColor3f(1.0f, 1.0f, 1.0f);

    myTexture.start();
    glBegin(GL_POLYGON);
        myTexture.markCoord(0, 0);       glVertex2f(0,0);
        myTexture.markCoord(1024, 0);    glVertex2f(946, 0);
        myTexture.markCoord(1024, 1024); glVertex2f(946, 451);
        myTexture.markCoord(0, 1024);    glVertex2f(0, 451);
    glEnd();

    // Disable texture mapping
    glDisable(GL_TEXTURE_2D);

    glutSwapBuffers();
}