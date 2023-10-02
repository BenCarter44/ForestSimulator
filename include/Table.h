#ifndef TABLE_H
#define TABLE_H

#include "DisplayObject.h"
#include "Window.h" // for the map function
#include <iostream>

class Table: public DisplayObject
{
private:
    float out_maxX;
    float out_minX;
    float in_minX;
    float in_maxX;

    float out_maxY;
    float out_minY;
    float in_minY;
    float in_maxY;
public:
    Table();
    void draw();
    float mapX(float x);
    float mapY(float x);

};

#endif