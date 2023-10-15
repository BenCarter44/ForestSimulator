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