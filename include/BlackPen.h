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