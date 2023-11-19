/**
 * @file Mesh.cpp
 * @author Benjamin Carter and Josh Canode
 * @brief The Mesh Class Source File. Creates a mesh terrain.
 * @version 1.0
 * @date 2023-11-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "Mesh.h"

Mesh::Mesh()
{
    normalSetup = false;
}
Mesh::Mesh(float division, float start, float end, float floor, float (*yFunc)(float, float) )
{
    totalPoints = division * division * 4;
    meshPoints = new glm::vec3[totalPoints];
    totalCubePoints = division * division;
    cubePoints = new glm::vec3[totalCubePoints];
    sidePoints = new glm::vec3[totalPoints * 4];
    div = division;
    this->start = start;
    this->end = end;
    this->floorY = floor;
    yFunction = yFunc;
    normalSetup = true;
}
Mesh::~Mesh()
{
    if(!normalSetup)
    {
        delete[] meshPoints;
        delete[] cubePoints;
        delete[] sidePoints;
    }
}
void Mesh::setup()
{
    int meshCount = 0;
    int cubeCount = 0;
    int sideCount = 0;
    for(float iy = 0; iy < div; iy++)
    {
        float adjY = mapF(iy, 0, div, start, end);
        float adjYnext = mapF(iy + 1, 0, div, start, end);
        for(float ix = 0; ix < div; ix++)
        {
            float adjX = mapF(ix, 0, div, start, end);
            float adjXnext = mapF(ix + 1, 0, div, start, end);

            float adjXhalf = mapF(ix + 0.5, 0, div, start, end);
            float adjYhalf = mapF(iy + 0.5, 0, div, start, end);
            float z = yFunction(adjXhalf, adjYhalf);

            cubePoints[cubeCount].x = adjXhalf;
            cubePoints[cubeCount].z = adjYhalf;
            cubePoints[cubeCount].y = z;
            cubeCount++;

            // start, start
            meshPoints[meshCount].x = adjX;
            meshPoints[meshCount].y = z;
            meshPoints[meshCount].z = adjY;
            meshCount++;

            // start, start + division
            meshPoints[meshCount].x = adjX;
            meshPoints[meshCount].y = z;
            meshPoints[meshCount].z = adjYnext;
            meshCount++;

            // start + division, start + division
            meshPoints[meshCount].x = adjXnext;
            meshPoints[meshCount].y = z;
            meshPoints[meshCount].z = adjYnext;
            meshCount++;

            // start + division, start
            meshPoints[meshCount].x = adjXnext;
            meshPoints[meshCount].y = z;
            meshPoints[meshCount].z = adjY;
            meshCount++;

            // sides now.
            for(int j = 0; j < 4; j++)
            {
            int firstPoint = -4 + j + meshCount;
            int secondPoint = -4 + (j + 1) % 4 + meshCount;

            sidePoints[sideCount] = meshPoints[firstPoint];
            sideCount++;
            sidePoints[sideCount] = meshPoints[secondPoint];
            sideCount++;
            sidePoints[sideCount] = meshPoints[secondPoint];
            sidePoints[sideCount].y = floorY;
            sideCount++;
            sidePoints[sideCount] = meshPoints[firstPoint];
            sidePoints[sideCount].y = floorY;
            sideCount++;
            }
        }
    }
}
glm::vec3* Mesh::getTopPoints()
{
    return meshPoints;
}
int Mesh::numberTopPoints()
{
    return totalPoints;
}

glm::vec3* Mesh::getCubePoints()
{
    return cubePoints;
}
int Mesh::numberCubePoints()
{
    return totalCubePoints;
}

glm::vec3* Mesh::getSidePoints()
{
    return sidePoints;
}

int Mesh::numberSidePoints()
{
    return totalPoints * 4;
}

float Mesh::getSquareWidth()
{
    return abs(end - start) / div; 
}