/**
 * @file Cup4.h
 * @author Benjamin Carter, Josh Canode.
 * @brief HeaderFile for the Cup4 class.
 * creates the 4th cup object using the multiPolygon class.
 * @version 0.1
 * @date 2023-10-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef CUP4_H
#define CUP4_H

#include "DisplayObject.h"
#include "Window.h"
#include <iostream>
#include "Polygon.h"
#include "MultiPolygon.h"
#include "TextureHandler.h"

class Cup4: public DisplayObject
{
private:
    Texture cupTexture;
public:
    Cup4();
    void draw();
    void postWindowCreate();
};

#endif