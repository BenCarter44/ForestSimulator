#include "TestTexture.h"

TestTexture::TestTexture()
{

}

void TestTexture::postWindowCreate()
{
    textureID = SOIL_load_OGL_texture(
        "textures/wood.png",  // Replace with the path to your .jpg file
        SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y
    );

    if (!textureID) {
        printf("Error loading texture: %s\n", SOIL_last_result());
    }
}

void TestTexture::draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
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