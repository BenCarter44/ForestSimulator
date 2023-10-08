/**
 * @file Cup2.h
 * @author Benjamin Carter, Josh Canode.
 * @brief HeaderFile for the Cup2 class.
 * creates the second cup object using the multiPolygon class.
 * @version 0.1
 * @date 2023-10-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef CUP2_H
#define CUP2_H

#include "DisplayObject.h"
#include "Window.h"
#include <iostream>
#include "Polygon.h"
#include "MultiPolygon.h"

class Cup2: public DisplayObject
{
public:
    Cup2();
    void draw();
};

#endif