/**
 * @file Cup1.h
 * @author Benjamin Carter, Josh Canode.
 * @brief HeaderFile for the Cup1 class.
 * Creates the fisrt cup object using the multiPolygon class.
 * @version 0.1
 * @date 2023-09-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef CUP1_H
#define CUP1_H

#include "DisplayObject.h"
#include "Window.h"
#include <iostream>
#include "Polygon.h"
#include "MultiPolygon.h"
#include "TextureHandler.h"

class Cup1: public DisplayObject
{
private:
    Texture cupTexture;
public:
    Cup1();
    void draw();
    void postWindowCreate();
};

#endif