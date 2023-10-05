#ifndef ORANGE_H
#define ORANGE_H

#include "DisplayObject.h"
#include "Window.h"
#include <iostream>
#include "Polygon.h"
#include "MultiPolygon.h"

class Orange: public DisplayObject
{
public:
    Orange();
    void draw();
};

#endif