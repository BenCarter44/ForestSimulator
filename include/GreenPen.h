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