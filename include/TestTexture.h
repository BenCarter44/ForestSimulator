#ifndef TEST_TEXTURE_H
#define TEST_TEXTURE_H

#include "DisplayObject.h"
#include "Window.h"
#include <iostream>
#include "Polygon.h"
#include "MultiPolygon.h"
#include <SOIL/SOIL.h>



class TestTexture: public DisplayObject
{
private:
    GLuint textureID;
public:
    TestTexture();
    void draw();
    void postWindowCreate();
    
};


#endif