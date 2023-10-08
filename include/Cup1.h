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