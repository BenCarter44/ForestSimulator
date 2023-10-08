/**
 * @file main.cpp
 * @author Benjamin Carter, Josh Canode.
 * @brief HeaderFile for the Cup1 class.
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

class Cup1: public DisplayObject
{
public:
    Cup1();
    void draw();
};

#endif