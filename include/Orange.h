/**
 * @file Orange.h
 * @author Benjamin Carter, Josh Canode.
 * @brief HeaderFile for the Orange class.
 * @version 0.1
 * @date 2023-10-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef ORANGE_H
#define ORANGE_H

#include "DisplayObject.h"
#include "Window.h"
#include <iostream>
#include "Polygon.h"
#include "MultiPolygon.h"

class Orange: public DisplayObject
{
private:
    Texture orangeTexture;
public:
    Orange();
    void postWindowCreate();
    void draw();
};

#endif