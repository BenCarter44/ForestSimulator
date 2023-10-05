#ifndef TABLE_H
#define TABLE_H

#include "DisplayObject.h"
#include "Window.h"
#include <iostream>
#include "Polygon.h"
#include "MultiPolygon.h"

class Table: public DisplayObject
{
public:
    Table();
    void draw();
};

#endif