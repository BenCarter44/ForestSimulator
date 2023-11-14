#include "TextWriter.h"

void TextWriter::renderBitmapString(float x, float y, void *font, const char* string)
{
    glRasterPos2f(x, y);
    int counter = 0;
    char c = string[0];
    while(c != '\0')
    {
        c = string[counter];
        glutBitmapCharacter(font, c);
        counter++;
    }
}

TextWriter::TextWriter(void* font, int screenWidth, int screenHeight)
{
    ft = font;
    glDisable(GL_TEXTURE_2D); //added this
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0.0, screenWidth, 0.0, screenHeight);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;

}
void TextWriter::write(float x, float y, const char* string)
{
    renderBitmapString(Mesh::mapF(x,-1,1,0,screenWidth),Mesh::mapF(y,-1,1,0,screenHeight),ft, string);
}

void TextWriter::close()
{
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glEnable(GL_TEXTURE_2D);
}