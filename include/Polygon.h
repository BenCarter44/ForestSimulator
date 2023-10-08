/**
 * @file multiPolygon.h
 * @author Benjamin Carter, Josh Canode.
 * @brief HeaderFile for the Polygon class.
 * @version 0.1
 * @date 2023-10-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */


//Original version of the Polygon class, This was replaced by multiPolygon
#ifndef POLYGON_H
#define POLYGON_H

#include "DisplayObject.h"
#include <algorithm>
#include <cmath>
#include <iostream>


#ifndef PI
#define PI           3.14159265358979323846  /* pi */
#endif

struct Point {
        double x;
        double y;

        void rotate(float deg, Point center)
        {
            float dist = sqrt((x - center.x) * (x - center.x) + (y - center.y) * (y - center.y));
            x = center.x + dist * cos((PI / 180.0) * -1 * deg);
            y = center.y + dist * sin((PI / 180.0) * -1 * deg);
        }
    };

struct Face {
    Point points[4];
    uint8_t r;
    uint8_t g;
    uint8_t b;
    int zindex;

    Face(Point aP, Point bP, Point cP, Point dP)
    {
        points[0] = aP;
        points[1] = bP;
        points[2] = cP;
        points[3] = dP;
        r = 255;
        g = 255;
        b = 255;
        zindex = 0; // render order.
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
    /**
     * @brief 
     * 
     * @param reference 
     * @param p1 
     * @param p2 
     * @return true 
     * @return false 
     */
    static bool closerToReference(Point reference, Point p1, Point p2);
    static bool comparePoints(Point reference, Point p1, Point p2);
    void sortPointsCounterclockwise(Point* arr, int len);
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
    /**
     * @brief Number of points passed in.
     * 
     */
    int pointsLength;

    /**
     * @brief Point array.
     * 
     */
    Point* pointsList;
    
    /**
     * @brief Array of faces. The array is sorted by face area. For coloring.
     * 
     */
    Face** faceList;

    /**
     * @brief The array of faces. Sorted by rendering.
     * 
     */
    Face** faceListOriginal;
};

#endif