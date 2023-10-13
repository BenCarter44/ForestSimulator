/**
 * @file Table.h
 * @author Benjamin Carter, Josh Canode.
 * @brief HeaderFile for the Table class.
 * @version 0.1
 * @date 2023-10-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef TABLE_H
#define TABLE_H

#include "DisplayObject.h"
#include "Window.h"
#include <iostream>
#include "Polygon.h"
#include "MultiPolygon.h"
#include "TextureHandler.h"

class Table: public DisplayObject
{
private:
    Texture woodTopTex;
public:
    Table();
    void draw();
    void postWindowCreate();
};

#endif