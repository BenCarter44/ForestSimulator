/**
 * @file Mesh.h
 * @author Benjamin Carter and Josh Canode
 * @brief This holds the Mesh class definitions.
 * @version 1.0
 * @date 2023-11-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef MESH_H
#define MESH_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/**
 * @brief The Mesh class creates "ground" terrain given starting x, y, and a function.
 * 
 */
class Mesh
{
  
private:
    glm::vec3* meshPoints;
    glm::vec3* cubePoints;
    glm::vec3* sidePoints;
    float div;
    float start;
    float end;
    int totalPoints;
    int totalCubePoints;
    float floorY;
    float (*yFunction)(float, float);
    bool normalSetup;

public:
    /**
     * @brief Empty constructor. Should not be used. Exists only for the "new" keyword.
     * 
     */
    Mesh();

    /**
     * @brief Construct a new Mesh.
     * 
     * @param division - How many "squares" per side of the mesh?
     * @param start - start at what x value (x and z both start here)
     * @param end - end at what x value (x and z both end here)
     * @param floor - the floor y value that the rectangles are drawn to
     * @param yFunc - a function pointer that returns the y value given the x,z coordinate.
     */
    Mesh(float division, float start, float end, float floor, float (*yFunc)(float, float) );

    /**
     * @brief Destroy the Mesh object
     * 
     */
    ~Mesh();

    /**
     * @brief Setup the mesh. This creates the mesh and performs the calculations. This MUST be called before further use.
     * 
     */
    void setup();
    
    /**
     * @brief Get an array of vec3 of the top square points (for drawing)
     * 
     * @return glm::vec3* 
     */
    glm::vec3* getTopPoints();
    /**
     * @brief Return the number of elements in the getTopPoints() array.
     * 
     * @return int 
     */
    int numberTopPoints();

    /**
     * @brief Get an array of vec3 of the center of the top of each cell.
     * 
     * @return glm::vec3* 
     */
    glm::vec3* getCubePoints();
    /**
     * @brief Return the number of elements in the getCubePoints() array.
     * 
     * @return int 
     */
    int numberCubePoints();

    /**
     * @brief Get an array of vec3 of all the side points in drawing order
     * 
     * @return glm::vec3* 
     */
    glm::vec3* getSidePoints();
    /**
     * @brief Return the number of points in the getSidePoints() array.
     * 
     * @return int 
     */
    int numberSidePoints();

    /**
     * @brief Get the width of a cell.
     * 
     * @return float 
     */
    float getSquareWidth();

    /**
     * @brief Basic linear mapping function.
     * 
     * @param x 
     * @param in_min 
     * @param in_max 
     * @param out_min 
     * @param out_max 
     * @return float 
     */
    static float mapF(float x, float in_min, float in_max, float out_min, float out_max) 
    {
      return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    }

    /**
     * @brief The maping function, but interpolates between two different colors.
     * 
     * @param change 
     * @param x - 0 to 1. 0 is first color, 1 is second.
     * @param r 
     * @param g 
     * @param b 
     * @param r2 
     * @param g2 
     * @param b2 
     */
    static void mixColor(float change[3], float x, int r, int g, int b, int r2, int g2, int b2)
    {
        change[0] = mapF(x, 0.0f, 1.0f,r, r2);
        change[1] = mapF(x, 0.0f, 1.0f,g, g2);
        change[2] = mapF(x, 0.0f, 1.0f,b, b2);
    }

};

#endif