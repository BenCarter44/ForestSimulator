#include "TestTexture.h"

TestTexture::TestTexture()
{
   /* const char* filename = "wood.jpg";
    int width, height;
    // Load and create a texture 
    // ====================
    // Texture 1
    // ====================
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
    // Set our texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Set texture filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Load, create texture and generate mipmaps
    
    unsigned char* image = SOIL_load_image("Container1.jpg", &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
    */
}

void TestTexture::drawTexturedRect(int x, int y, int w, int h, GLuint texture){
  
    // glEnable(GL_TEXTURE_2D);
    // glBindTexture(GL_TEXTURE_2D, texture);
    // glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // glDepthMask(GL_FALSE);
    // glDisable(GL_DEPTH_TEST);
    // glBegin(GL_QUADS);
    //     glColor3f(255,255,255);
    //     glTexCoord2f(0,0);
    //     glVertex2f(x,y);
    //     glTexCoord2f(1,0);
    //     glVertex2f(x+w,y);
    //     glTexCoord2f(0,1);
    //     glVertex2f(x,y+h);
    //     glTexCoord2f(1,1);
    //     glVertex2f(x+w,y+h);
    //     glTexCoord2f(0,1);
    //     glVertex2f(x,y+h);
    // glEnd();
    // glEnable(GL_DEPTH_TEST);
    // glDepthMask(GL_TRUE);
    // glDisable(GL_BLEND);
}

void TestTexture::draw()
{
  //  drawTexturedRect(0,0, 946, 451,texture);
}