/**
 * @file Cup3.h
 * @author Benjamin Carter, Josh Canode.
 * @brief HeaderFile for the Cup3 class.
 * creates the third cup object using the multiPolygon class.
 * @version 0.1
 * @date 2023-10-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef CUP3_H
#define CUP3_H

#include "DisplayObject.h"
#include "Window.h"
#include <iostream>
#include "Polygon.h"
#include "MultiPolygon.h"
#include "TextureHandler.h"

class Cup3: public DisplayObject
{
private:
    Texture cupTexture;
public:
    Cup3();
    void draw();
    void postWindowCreate();
};

#endif