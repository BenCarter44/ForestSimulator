#ifndef TEXTUREHANDLER_HANDLER_H
#define TEXTUREHANDLER_HANDLER_H

#include "DisplayObject.h"
#include <SOIL/SOIL.h>
#include <iostream>

#include <string>

class Texture
{
private:
    GLuint textureID;
    std::string filename;

    int size; 
    int id;   

public:
    Texture();
    Texture(const char* filename);
    Texture(const char* filename, int size);
    int setupTexture();
    void start();
    void stop();
    void markCoord(float x, float y);
};




#endif