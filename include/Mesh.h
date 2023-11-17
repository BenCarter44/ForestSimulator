
#ifndef MESH_H
#define MESH_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
    Mesh();
    Mesh(float division, float start, float end, float floor, float (*yFunc)(float, float) );
    ~Mesh();

    void setup();
    
    glm::vec3* getTopPoints();
    int numberTopPoints();

    glm::vec3* getCubePoints();
    int numberCubePoints();

    glm::vec3* getSidePoints();
    int numberSidePoints();

    float getSquareWidth();

    static float mapF(float x, float in_min, float in_max, float out_min, float out_max) 
    {
      return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    }

    static void mixColor(float change[3], float x, int r, int g, int b, int r2, int g2, int b2)
    {
        change[0] = mapF(x, 0.0f, 1.0f,r, r2);
        change[1] = mapF(x, 0.0f, 1.0f,g, g2);
        change[2] = mapF(x, 0.0f, 1.0f,b, b2);
    }

};

#endif