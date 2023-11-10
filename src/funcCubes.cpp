#include <GL/glut.h>
#include <cmath>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#ifndef CC
#define CC(arg) (arg / 255.0f)
#endif

void frame(int a);
using namespace std;

float mapF(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

float myFunction(float x, float z)
{
    return cos((x - 1) / 2.0f) + cos((z - 2) / 2.0f) + 0.1 * sin(x - 1);

}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)width / (float)height, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}


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
public:
    Mesh(float division, float start, float end, float floor)
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
    }
    ~Mesh()
    {
        delete[] meshPoints;
        delete[] cubePoints;
        delete[] sidePoints;
    }
    void setupMesh()
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
                float z = myFunction(adjXhalf, adjYhalf);

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
    glm::vec3* getTopPoints()
    {
        return meshPoints;
    }
    int numberTopPoints()
    {
        return totalPoints;
    }

    glm::vec3* getCubePoints()
    {
        return cubePoints;
    }
    int numberCubePoints()
    {
        return totalCubePoints;
    }

    glm::vec3* getSidePoints()
    {
        return sidePoints;
    }

    int numberSidePoints()
    {
        return totalPoints * 4;
    }

};


void renderScene(void)
{

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity(); // clears all transformations and what not.

  gluLookAt(15,4.5,10, // The position of the camera
      0.0, 0.0, 0.0f, // face what point
      0.0f, 1.0f, 0.0f // camera rotation.
      );

  frame(0);
}

void frame(int ignore)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   // sets the matrix mode
    
  glBegin(GL_LINES);
    glColor3f(255.0f,0.0f,0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(5.0f, 0.0f, 0.0f);

    glColor3f(0.0f,0.0f,255.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 5.0f, 0.0f);

    glColor3f(0.0f,255.0f,0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 5.0f);

  glEnd();

  Mesh myMesh = Mesh(20, 0, 10, -3);
  myMesh.setupMesh();
  glColor3f(CC(95), CC(171), CC(37));
  glBegin(GL_QUADS);
    glm::vec3* points = myMesh.getTopPoints();
    for(int i = 0; i < myMesh.numberTopPoints(); i++)
    {
        glVertex3f(points[i].x - 5,points[i].y,points[i].z - 5);
    }
    glEnd();

  glPointSize(4);
  glBegin(GL_POINTS);
  glColor3f(CC(255), CC(255), CC(255));
    glm::vec3* pointsCenter = myMesh.getCubePoints();
    for(int i = 0; i < myMesh.numberCubePoints(); i++)
    {
        glVertex3f(pointsCenter[i].x - 5,pointsCenter[i].y,pointsCenter[i].z - 5);
    }
    glEnd();

  glColor3f(CC(110), CC(64), CC(28));
  glPointSize(1);
  glBegin(GL_QUADS);
  glm::vec3* pointsSide = myMesh.getSidePoints();
    for(int i = 0; i < myMesh.numberSidePoints(); i++)
    {
        glVertex3f(pointsSide[i].x - 5,pointsSide[i].y,pointsSide[i].z - 5);
    }
    glEnd();

 
  glutSwapBuffers();
}


void idleFunction()
{
  
}


int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_SINGLE | GLUT_RGBA);
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(640, 640);
  glutCreateWindow("A Function in 3D");
  glutDisplayFunc(renderScene);
  glutIdleFunc(idleFunction);
  glutReshapeFunc(reshape);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_PROGRAM_POINT_SIZE);
  glutMainLoop();
  return 0;
}
