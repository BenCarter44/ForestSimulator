/**
 * @file CatchPhrase.h
 * @author Benjamin Carter, Josh Canode.
 * @brief HeaderFile for the CatchPhrase class.
 * @version 0.1
 * @date 2023-10-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */
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