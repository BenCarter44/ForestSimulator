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