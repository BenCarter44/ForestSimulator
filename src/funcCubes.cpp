#include <GL/glut.h>
#include <cmath>
#include <iostream>

#include "Mesh.h"
#include <stdio.h>
#include <time.h>
#include <ctime>
#include <cstdlib>  // for rand() and srand()
#include "TextWriter.h"
#include "Trees.h"

#ifndef CC
#define CC(arg) (arg / 255.0f)
#endif


#define TARGET_FPS 120.0f
// Globals.
Mesh groundMesh = Mesh();
glm::vec4 camPos;
unsigned int frameCount = 0;
float currentTime = 0;
float timeFPSOffset = 0;
float fps = 0.0f;
float writeoutFPS = fps;
int screenHeight = 0;
int screenWidth = 0;
ForestAnimationSettings forestSettings;

// Trees
Tree** allTrees;


float groundFunction(float x, float z)
{
    return cos((x - 1) / 2.0f) + cos((z - 2) / 2.0f) + 0.1 * sin(x - 1);
}

void reshape(int width, int height)
{
    screenHeight = height;
    screenWidth = width;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)width / (float)height, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

void renderAxes()
{
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
}

void renderGround()
{
    glColor3f(CC(95), CC(171), CC(37));
    glBegin(GL_QUADS);
    glm::vec3* points = groundMesh.getTopPoints();
    for(int i = 0; i < groundMesh.numberTopPoints(); i++)
    {
        glVertex3f(points[i].x - 5,points[i].y,points[i].z - 5);
    }
   glEnd();

    glColor3f(CC(110), CC(64), CC(28));
    glBegin(GL_QUADS);
    glm::vec3* pointsSide = groundMesh.getSidePoints();
    for(int i = 0; i < groundMesh.numberSidePoints(); i++)
    {
        glVertex3f(pointsSide[i].x - 5,pointsSide[i].y,pointsSide[i].z - 5);
    }
    glEnd();
}

void renderCamera(void)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); // clears all transformations and what not.

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(currentTime * 8), glm::vec3(0, 1, 0) );

    // apply the model to the vertex.
    glm::vec3 camPosAdjust = model * camPos;
    gluLookAt(camPosAdjust.x, camPosAdjust.y, camPosAdjust.z, // The position of the camera
             0.0, 0.0, 0.0f, // face what point
             0.0f, 1.0f, 0.0f // camera rotation.
      );
}

void frame()
{
    renderCamera();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    renderAxes();
     renderGround();

    // glPointSize(2);
    // glBegin(GL_POINTS);
    // glColor3f(CC(255), CC(255), CC(255));
    // glm::vec3* pointsCenter = groundMesh.getCubePoints();
    // for(int i = 0; i < groundMesh.numberCubePoints(); i++)
    // {
    //     glVertex3f(pointsCenter[i].x - 5,pointsCenter[i].y,pointsCenter[i].z - 5);
    // }

    // glEnd();
   // glPointSize(1);

 //   render the trees.
    for(int i = 0; i < groundMesh.numberCubePoints(); i++)
    {
        allTrees[i]->draw();
    }
   
    // render FPS.
    glColor3f(CC(255), CC(255), CC(255));
    TextWriter tw = TextWriter(GLUT_BITMAP_9_BY_15, screenWidth, screenHeight);
    char buff[20];
    sprintf(buff, "FPS: %4.1f",writeoutFPS);
    tw.write(-0.95, 0.92, buff);
    tw.close();

    glFlush();
    glutSwapBuffers();
}

void timer(int a)
{
    frameCount = a;
    timeFPSOffset = currentTime;
    currentTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;

    fps = 0.8 * (1 / (currentTime - timeFPSOffset + 0.00001)) + 0.2 * fps;

    glutPostRedisplay();
    glutTimerFunc(1000.0 / (0.7 * TARGET_FPS + 0.3 * fps), timer, a + 1); 
}

void idleFunction()
{
    if(frameCount % ((int)(0.5 * fps) + 1) == 0 && abs(fps - writeoutFPS) > 0.05)
    {
    //    std::cout << frameCount << std::endl;
        writeoutFPS = fps;
    }
}

void setupCalculations()
{
    std::srand(std::time(0) * 2.0f - 22);
    groundMesh = Mesh(50, 0, 8, -3, groundFunction);
    groundMesh.setup();

    allTrees = new Tree*[groundMesh.numberCubePoints()];
    glm::vec3* pointsCenter = groundMesh.getCubePoints();

    float squareWidth = groundMesh.getSquareWidth();

    for(int i = 0; i < groundMesh.numberCubePoints(); i++)
    {
        glm::vec3 position = glm::vec3(pointsCenter[i].x - 5,pointsCenter[i].y,pointsCenter[i].z - 5);

        float treeWidth = squareWidth * 0.6;
        float randomHeight = Mesh::mapF(std::rand(), 0, RAND_MAX, 0.2, 1);
        glm::vec3 dimensions = glm::vec3(treeWidth, randomHeight, treeWidth);

        allTrees[i] = new Tree(position, dimensions, &forestSettings, &fps);
    }

    camPos = glm::vec4(15.0f, 4.5f, 10.0f, 0.0f);

    renderCamera();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(640, 640);
    screenHeight = 640;
    screenWidth = 640;
    glutCreateWindow("A Function in 3D");
    glutDisplayFunc(frame);
    glutTimerFunc(100, timer, 0);
    glutIdleFunc(idleFunction);
    glutReshapeFunc(reshape);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_PROGRAM_POINT_SIZE);

    setupCalculations();
    glutMainLoop();
    return 0;
}
