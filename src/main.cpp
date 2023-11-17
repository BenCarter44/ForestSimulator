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
#include <vector>

#ifndef CC
#define CC(arg) (arg / 255.0f)
#endif


#define TARGET_FPS 120.0f
float UNITS_PER_SECOND = 0.5f;


#define MESH_DIVISIONS 65
// 65, and 22 are finest at fps
// 100, and 50 are for full screen.
#define MESH_START -22
#define MESH_END 22
#define MESH_DEPTH -3

#define MESH_TRANSLATE_X 0
#define MESH_TRANSLATE_Z 0

// Globals.
Mesh groundMesh = Mesh();
glm::vec4 camPos;
unsigned int frameCount = 0;
float currentTime = 0;
float timeFPSOffset = 0;
float fps = 0.0f;
float writeoutFPS = fps;
float unitCounter = 0.0f;

int screenHeight = 0;
int screenWidth = 0;
ForestAnimationSettings forestSettings;
float prevCamY = 0.0;

// Trees
Tree** allTrees;



float groundFunction(float x, float z)
{
    return cos((x - 1) / 2.0f) + cos((z - 2) / 2.0f) + 0.1 * sin(x - 1) + 0.05 * x;
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
   // glColor3f(CC(95), CC(171), CC(37));
    glColor3f(CC(97), CC(44), CC(15));
    glBegin(GL_QUADS);
    glm::vec3* points = groundMesh.getTopPoints();
    for(int i = 0; i < groundMesh.numberTopPoints(); i++)
    {
        glVertex3f(points[i].x + MESH_TRANSLATE_X,points[i].y,points[i].z + MESH_TRANSLATE_Z);
    }
   glEnd();

    // draw sides.
   // glColor3f(CC(110), CC(64), CC(28));
    glColor3f(CC(132), CC(60), CC(12));
    
    glBegin(GL_QUADS);
    glm::vec3* pointsSide = groundMesh.getSidePoints();
    for(int i = 0; i < groundMesh.numberSidePoints(); i++)
    {
        glVertex3f(pointsSide[i].x + MESH_TRANSLATE_X, pointsSide[i].y, pointsSide[i].z + MESH_TRANSLATE_Z);
    }
    glEnd();
}

void renderCamera(void)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); // clears all transformations and what not.


    // float x = cos(currentTime  / 10.0) * 7.75f;
    // float z = sin(currentTime  / 10.0) * 7.75f;

    // float groundY = groundFunction(x, z);

    // float x2 = cos((currentTime + 5)  / 10.0) * 7.75f;
    // float z2 = sin((currentTime + 5)  / 10.0) * 7.75f;
    // float y2 = groundFunction(x,z) ;

    // gluLookAt(x, groundY + 1.9, z, // The position of the camera
    //          x2, y2 + 1.5, z2, // face what point
    //          0.0f, 1.0f, 0.0f // camera rotation.
    //   );

    float x = cos(currentTime  / 10.0) * 18.0f;
    float z = sin(currentTime  / 10.0) * 18.0f;

    gluLookAt(x, 16, z, // The position of the camera
             0.0, 0.0, 0.0, // face what point
             0.0f, 1.0f, 0.0f // camera rotation.
      );


}

void frame()
{
    renderCamera();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    renderAxes();
    renderGround();

    for(int i = 0; i < groundMesh.numberCubePoints(); i++)
    {
        allTrees[i]->simulate();
        allTrees[i]->draw();
    }
    
    
    // render FPS.
    glColor3f(CC(255), CC(255), CC(255));
    TextWriter tw = TextWriter(GLUT_BITMAP_9_BY_15, screenWidth, screenHeight);
    char buff[40];
    sprintf(buff, "FPS: %4.1f",writeoutFPS);
    tw.write(-0.95, 0.92, buff);
    sprintf(buff, "Years: %4.1f",unitCounter);
    tw.write(-0.95, 0.85, buff);

    sprintf(buff, "Alive Tree: %d",Tree::numberOfTreesAlive);
    tw.write(-0.95, 0.80, buff);
    sprintf(buff, "Burning Tree: %d",Tree::numberOfTreesBurning);
    tw.write(-0.95, 0.75, buff);
    sprintf(buff, "Burned Tree: %d",Tree::numberOfTreesBurned);
    tw.write(-0.95, 0.70, buff);
    sprintf(buff, "Bare Rock: %d",Tree::numberOfNoTrees);
    tw.write(-0.95, 0.65, buff);

    sprintf(buff, "Number Of Fires Started: %d", Tree::numberOfFireStarts);
    tw.write(-0.95, 0.58, buff);

    tw.close();

    //std::cout << '\n';
    glFlush();
    glutSwapBuffers();
}

void timer(int a)
{
    frameCount = a;
    timeFPSOffset = currentTime;
    currentTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
    if(frameCount > 10)
    {
        unitCounter += (currentTime - timeFPSOffset) * UNITS_PER_SECOND;
    }

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

void get_neighbors(int i, std::vector<Tree*> &foundNeighbors, Tree** allTrees, int allTreesLength)
{
    /* Convert the index into X and Y positions.*/ 
    int x_start = i % MESH_DIVISIONS;
    int y_start = i / MESH_DIVISIONS;

    for(int x = x_start - 1; x <= x_start+1; x++)
    {
        if (x < 0 || x >= MESH_DIVISIONS)
        {
            continue;
        }

        for (int y = y_start - 1; y <= y_start+1; y++)
        {   
            if (y < 0 || y >= MESH_DIVISIONS)
            {
                continue;
            }
            if (x == x_start && y == y_start)
            {
                continue;
            }
            int checkIndex = x + MESH_DIVISIONS * y;
            if(checkIndex < 0 || checkIndex >= allTreesLength)
            {
                continue;
            }
            foundNeighbors.push_back(allTrees[checkIndex]);
        }
    }
}

void setupCalculations()
{
    unitCounter = 0.0;
    std::srand(std::time(0) * 2.0f - 22);
    
    /*
    Mesh!!
    */
    groundMesh = Mesh(MESH_DIVISIONS, MESH_START, MESH_END, MESH_DEPTH, groundFunction);
    groundMesh.setup();

    /* Create the tree array */
    allTrees = new Tree*[groundMesh.numberCubePoints()]; 
    glm::vec3* pointsCenter = groundMesh.getCubePoints();

    float squareWidth = groundMesh.getSquareWidth();

    for(int i = 0; i < groundMesh.numberCubePoints(); i++)
    {
        glm::vec3 position = glm::vec3(pointsCenter[i].x + MESH_TRANSLATE_X,pointsCenter[i].y,pointsCenter[i].z + MESH_TRANSLATE_Z);

        float treeWidth = squareWidth * 0.6;
        float randomHeight = Mesh::mapF(std::rand(), 0, RAND_MAX, 0.2, 1);
        glm::vec3 dimensions = glm::vec3(treeWidth, randomHeight, treeWidth);

        allTrees[i] = new Tree(position, dimensions, &forestSettings, &fps, UNITS_PER_SECOND, &unitCounter);
        allTrees[i]->incrementAge(forestSettings.TREE_INITIAL_AGE);
    }
    
    for(int i = 0; i < groundMesh.numberCubePoints(); i++)
    {
        std::vector<Tree*> foundNeighbors;
        get_neighbors(i,foundNeighbors, allTrees, groundMesh.numberCubePoints());
        
        Tree** neighbors = new Tree*[foundNeighbors.size() > 0 ? foundNeighbors.size() : 1];
        std::copy(foundNeighbors.begin(), foundNeighbors.end(), neighbors);

        int numberOfNeighbors = foundNeighbors.size();
        allTrees[i]->setNeighborData(neighbors, numberOfNeighbors);
    }

    camPos = glm::vec4(15.0f, 7.5f, 10.0f, 0.0f);
    
   // glClearColor(CC(131), CC(228), CC(233), 1.0f);
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
    glutCreateWindow("Forest Lifecycle Simulator");
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
