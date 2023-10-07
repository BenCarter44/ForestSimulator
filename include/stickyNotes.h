#ifndef stickyNotes_H
#define stickyNotes_H

#include "DisplayObject.h"
#include "Window.h"
#include <iostream>
#include "Polygon.h"
#include "MultiPolygon.h"

class stickyNotes: public DisplayObject
{
public:
    stickyNotes();
    void draw();
};  

#endif