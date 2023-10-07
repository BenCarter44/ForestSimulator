#ifndef CUP4_H
#define CUP4_H

#include "DisplayObject.h"
#include "Window.h"
#include <iostream>
#include "Polygon.h"
#include "MultiPolygon.h"

class Cup4: public DisplayObject
{
public:
    Cup4();
    void draw();
};

#endif