#ifndef CUP3_H
#define CUP3_H

#include "DisplayObject.h"
#include "Window.h"
#include <iostream>
#include "Polygon.h"
#include "MultiPolygon.h"

class Cup3: public DisplayObject
{
public:
    Cup3();
    void draw();
};

#endif