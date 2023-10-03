#ifndef POLYGON_H
#define POLYGON_H

#include "DisplayObject.h"
#include <algorithm>
#include <cmath>

struct Point {
        double x;
        double y;
    };

class Polygon
{
private:
    int pointsLength;

    static bool closerToReference(Point reference, Point p1, Point p2);
    static bool comparePoints(Point reference, Point p1, Point p2);
    void sortPointsCounterclockwise(Point arr[8]);
    void drawShape(Point arr[4], int color);
public:
    static double polarAngle(Point reference, Point p);
    Polygon(Point* pointsList, int pointsLength);
    void draw();

private:
    Point* pointsList;
};

#endif