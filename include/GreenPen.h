/**
 * @file GreenPen.h
 * @author Benjamin Carter, Josh Canode.
 * @brief HeaderFile for the GreenPen class.
 * @version 0.1
 * @date 2023-10-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef GREENPEN_H
#define GREENPEN_H

#include "DisplayObject.h"
#include "Window.h"
#include <iostream>
#include "Polygon.h"
#include "MultiPolygon.h"

class GreenPen: public DisplayObject
{
public:
    GreenPen();
    void draw();
};

#endif