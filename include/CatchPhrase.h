#ifndef CATCHPHRASE_H
#define CATCHPHRASE_H

#include "DisplayObject.h"
#include "Window.h"
#include <iostream>
#include "Polygon.h"
#include "MultiPolygon.h"

class CatchPhrase: public DisplayObject
{
public:
    CatchPhrase();
    void draw();
};

#endif