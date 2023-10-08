/**
 * @file Test.h
 * @author Benjamin Carter, Josh Canode.
 * @brief HeaderFile for the Test class.
 * @version 0.1
 * @date 2023-10-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef TEST_H
#define TEST_H

#include "DisplayObject.h"
#include "Window.h"
#include <iostream>
#include "Polygon.h"
#include "MultiPolygon.h"

class Test: public DisplayObject
{
public:
    Test();
    void draw();
};

#endif