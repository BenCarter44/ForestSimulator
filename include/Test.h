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