/**
 * @file TestTexture.h
 * @author Benjamin Carter and Josh Canode
 * @brief Test Texture display object that tests the Texture class.
 * @version 0.1
 * @date 2023-10-14
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef TEST_TEXTURE_H
#define TEST_TEXTURE_H

#include "DisplayObject.h"
#include "Window.h"
#include <iostream>
#include "Polygon.h"
#include "MultiPolygon.h"
#include <SOIL/SOIL.h>
#include "TextureHandler.h"


class TestTexture: public DisplayObject
{
private:
    Texture myTexture;
public:
    TestTexture();
    void draw();
    void postWindowCreate();
    
};


#endif