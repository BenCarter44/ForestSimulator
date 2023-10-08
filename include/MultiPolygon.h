/**
 * @file MultiPolygon.h
 * @author Benjamin Carter, Josh Canode.
 * @brief HeaderFile for the MultiPolygon class.
 * @version 0.1
 * @date 2023-10-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */
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


/*
    A__________B
   /           /| 
C /_________D_/ / F
  |___________|/
  G           H    

  (E is behind) 

  An Anchor face is where all the 'wall' faces attach.

  AnchorFace 1 (the top): ABDC   ( there is a reason for this order... see below)
  AnchorFace 2 (the bottom): EFHG

  The walls. ABEF, BDFH, DCHG  (there is a reason for this order... see below) 

  A multiploygon takes two anchor faces and automatically draws the "walls" as well.

  It sorts the walls by the order of points in the anchor face. 
  (ABEF first, BDFH second), it groups it in groups of 2

  Currrently supports Convex shapes only. Concave shapes are undefined.

*/



/**
 * @brief An AnchorFace is the polygon that all the sides attach to
 * 
 */
struct AnchorFace {
    /**
     * @brief The points of the face. An array of points
     * 
     */
    Point* points;
    /**
     * @brief Number of points in the anchor face.
     * 
     */
    int numberPoints;

    /* The colors 0 - 255 */
    uint8_t r, g, b, a;

    AnchorFace(Point* points, int numberPoints)
    {
        this->points = points;
        this-> numberPoints = numberPoints;
        r = 255;
        g = 255;
        b = 255;
    }
    /**
     * @brief Set the Color of the face. 0-255 values.
     * 
     * @param rIn 
     * @param gIn 
     * @param bIn 
     */
    void setColor(uint8_t rIn, uint8_t gIn, uint8_t bIn)
    {
        r = rIn;
        g = gIn;
        b = bIn;
    }
};

/**
 * @brief Draw a many dimensional polygon. Note: ONLY SUPPORTS CONVEX shapes!!!!
 * 
 */
class MultiPolygon
{
private:
    /**
     * @brief Draw the shapes. An internal function.
     * 
     * @param arr 
     */
    void drawShape(Face* arr);
    /**
     * @brief The top anchor face
     * 
     */
    AnchorFace* top;
    /**
     * @brief The bottom anchor face
     * 
     */
    AnchorFace* bottom;
    /**
     * @brief An array of all the wall faces. An array of Face*
     * 
     */
    Face** allSides;
    /**
     * @brief The number of vertices of an anchor face.
     * Note: the number of vertices must be the same for each anchor face.
     * 
     */
    int numVert;

    // See: http://songho.ca/opengl/gl_tessellation.html

    /**
     * @brief Get all the wall faces. Does the calculations.
     * 
     */
    void getFaces();

public:
    /**
     * @brief Construct a new Multi-Polygon object
     * 
     * @param top The top anchor face. Passed as pointer
     * @param bottom The bottom anchor face. Passed as pointer
     */
    MultiPolygon(AnchorFace* top, AnchorFace* bottom);

    /**
     * @brief Draw the polygon
     * 
     */
    void draw();

    /**
     * @brief Destroy the Multi Polygon object
     * 
     */
    ~MultiPolygon();

    /**
     * @brief Get the number of walls
     * 
     * @return int 
     */
    int getColorFacesNum();

    /**
     * @brief Get the area of a face. Static.
     * 
     * @param arr 
     * @return double 
     */
    static double getArea(Face* arr);

    /**
     * @brief Get the walls (the faces that can be colored)
     * 
     * @return Face** 
     */
    Face** getColorFaces();
};

#endif