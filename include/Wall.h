/**
 * @file Wall.h
 * @author Benjamin Carter and Josh Canode
 * @brief Holds the Wall Display Object class.
 * @version 0.1
 * @date 2023-10-14
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef WALL_INCLUDE_H
#define WALL_INCLUDE_H

#include "TextureHandler.h"
#include "DisplayObject.h"
#include "Window.h"

class Wall: public DisplayObject
{
private:
    Texture wallTexture;
public:
    Wall();
    void draw();
    void postWindowCreate();
};


#endif