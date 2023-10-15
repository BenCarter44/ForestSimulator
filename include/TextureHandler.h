/**
 * @file TextureHandler.h
 * @author Benjamin Carter and Josh Canode
 * @brief Holds the Texture class. Used for texturing objects.
 * @version 0.1
 * @date 2023-10-14
 * 
 * @copyright Copyright (c) 2023
 * 
 */
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