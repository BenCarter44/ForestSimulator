#ifndef MULTPOLYGON_H
#define MULTPOLYGON_H

#include "DisplayObject.h"
#include <algorithm>
#include "Polygon.h"
#include <cmath>

#include <iostream>

#ifndef CALLBACK
#define CALLBACK
#endif

struct AnchorFace {
    Point* points;
    int numberPoints;
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;

    AnchorFace(Point* points, int numberPoints)
    {
        this->points = points;
        this-> numberPoints = numberPoints;
        r = 255;
        g = 255;
        b = 255;
    }
    void setColor(uint8_t rIn, uint8_t gIn, uint8_t bIn)
    {
        r = rIn;
        g = gIn;
        b = bIn;
    }
};

class MultiPolygon
{
private:
    void drawShape(Face* arr);
    AnchorFace* top;
    AnchorFace* bottom;
    Face** allSides;
    int numVert;

    // See: http://songho.ca/opengl/gl_tessellation.html

    void getFaces();

public:
    MultiPolygon(AnchorFace* top, AnchorFace* bottom);

    void draw();
    ~MultiPolygon();

    int getColorFacesNum();
    static double getArea(Face* arr);
    void setWallColor(int r, int g, int b);
    Face** getColorFaces();
};

#endif