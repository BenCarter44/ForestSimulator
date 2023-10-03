#ifndef TABLE_H
#define TABLE_H

#include "DisplayObject.h"
#include "Window.h" // for the map function
#include <iostream>
#include "Polygon.h"

class Table: public DisplayObject
{
public:
    Table();
    void draw();
    float mapX(float x);
    float mapY(float x);

};

#endif