/**
 * @file BlackPen.h
 * @author Benjamin Carter, Josh Canode.
 * @brief HeaderFile for the Black Pen Class.
 * @version 0.1
 * @date 2023-10-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef BLACKPEN_H
#define BLACKPEN_H

#include "DisplayObject.h"
#include "Window.h"
#include <iostream>
#include "Polygon.h"
#include "MultiPolygon.h"

class BlackPen: public DisplayObject
{
public:
    BlackPen();
    void draw();
};

#endif