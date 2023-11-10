#include <GL/glut.h>
#include <cmath>
#include <iostream>

#include "Mesh.h"
#include <stdio.h>
#include <time.h>

#ifndef CC
#define CC(arg) (arg / 255.0f)
#endif


// Globals.
Mesh groundMesh = Mesh();
glm::vec3 camPos;
unsigned int frameCount = 0;
float currentTime = 0;
float timeFPSOffset = 0;
float fps = 60.0f;
float oldFPS = fps;


float groundFunction(float x, float z)
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
    model = glm::rotate(model, glm::radians((float)frameCount), glm::vec3(0, 1, 0) );

    gluLookAt(15, 4.5, 10, // The position of the camera
             0.0, 0.0, 0.0f, // face what point
             0.0f, 1.0f, 0.0f // camera rotation.
      );
}

void frame()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // sets the matrix mode
    
    renderAxes();
    renderGround();

    glPointSize(2);
    glBegin(GL_POINTS);
    glColor3f(CC(255), CC(255), CC(255));
    glm::vec3* pointsCenter = groundMesh.getCubePoints();
    for(int i = 0; i < groundMesh.numberCubePoints(); i++)
    {
        glVertex3f(pointsCenter[i].x - 5,pointsCenter[i].y,pointsCenter[i].z - 5);
    }
    glEnd();

    glFlush();
    glutSwapBuffers();
}

void timer(int a)
{
    frameCount = a;
    timeFPSOffset = currentTime;
    currentTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;

    fps = 0.9 * (1 / (currentTime - timeFPSOffset + 0.00001)) + 0.1 * fps;

    glutPostRedisplay();
    glutTimerFunc(1000.0 / 60.0f, timer, a + 1); 
}

void idleFunction()
{
    if(frameCount % 30 == 0 && fps != oldFPS)
    {
        std::cout << fps << std::endl; 
        oldFPS = fps;
    }
}

void setupCalculations()
{
    groundMesh = Mesh(20, 0, 6, -3, groundFunction);
    groundMesh.setup();

    camPos = glm::vec3(15.0f, 4.5f, 10.0f);

    renderCamera();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(640, 640);
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
