#ifndef POLYGON_H
#define POLYGON_H

#include "DisplayObject.h"
#include <algorithm>
#include <cmath>

#include <iostream>

using namespace std;

struct Point {
        double x;
        double y;
    };

struct Face {
    Point points[4];
    uint8_t r;
    uint8_t g;
    uint8_t b;

    Face(Point aP, Point bP, Point cP, Point dP)
    {
        points[0] = aP;
        points[1] = bP;
        points[2] = cP;
        points[3] = dP;
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

class Polygon
{
private:
    int pointsLength;
    static bool closerToReference(Point reference, Point p1, Point p2);
    static bool comparePoints(Point reference, Point p1, Point p2);
    void sortPointsCounterclockwise(Point arr[8]);
    void drawShape(Face* arr);
    void getFaces();
public:
    static double polarAngle(Point reference, Point p);
    Polygon(Point* pointsList, int pointsLength);
    void draw();
    ~Polygon();
    Face** getColorFaces();
    int getNumberFaces();
    static double getArea(Face* arr);

private:
    Point* pointsList;
    Face** faceList;
    Face** faceListOriginal;
};

#endif