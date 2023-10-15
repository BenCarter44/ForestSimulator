/**
 * @file testSOILs.cpp
 * @author Benjamin Carter and Josh Canode
 * @brief Used to test Texture loading. It is a "separate" program.
 * @version 0.1
 * @date 2023-10-14
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifdef TESTTESTLIBQASLKDBALJBFLJBADF // NOT DEFINED! (IGNORE CODE)

#include "glIncludes.h"
#include <SOIL/SOIL.h>
#include <stdio.h>
#include <stdlib.h>
#include "Window.h"
#include "DisplayObject.h"



class TestObject : public DisplayObject
{
private:
     GLuint textureID;

public:
    TestObject()
    {

    }

    void draw()
    {
        glColor3f(1.0f, 1.0f, 1.0f);

        // Enable texture mapping
        glEnable(GL_TEXTURE_2D);

        // Bind the texture
        glBindTexture(GL_TEXTURE_2D, textureID);

        glBegin(GL_POLYGON);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(0,0);
        glTexCoord2f(1.0f, 0.0f); glVertex2f(946, 0);
        glTexCoord2f(1.0f, 1.0f); glVertex2f(946, 451);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(0, 451);
        glEnd();

        // Disable texture mapping
        glDisable(GL_TEXTURE_2D);

        glutSwapBuffers();
    }

    void postWindowCreate()
    {
        const char* fname = "wood.png";
        // Load the texture from a .jpg file
        textureID = SOIL_load_OGL_texture(
                fname,  // Replace with the path to your .jpg file
                SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y
            );

        if (!textureID) {
            printf("Error loading texture: %s\n", SOIL_last_result());
        }
        
    }

};

int main(int argc, char** argv)
{
    Window::initGL(argc, argv);
    Window myWindow = Window("OpenGL Mesh", 400, 400);

    TestObject myObject = TestObject();
    myWindow.addObject(&myObject);

   // loadTexture();  // Load the texture
    myWindow.launch();
    myWindow.mainLoop();
    //glutMainLoop();
    return 0;
}

#endif