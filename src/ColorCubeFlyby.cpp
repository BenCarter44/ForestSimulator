/**
 * @file ColorCubeFlyby.cpp
 * @author Benjamin Carter
 * @brief This program/animation animates cubes that bounce from one plane to another. The camera position is adjustable.
 * @version 1.0
 * @date 2023-11-08
 * 
 * @copyright Copyright (c) 2023
 * 
 * 
 *  It was taken from an in-class resource and then modified.
 */
#ifdef PART2BUILD

#include <GL/glut.h>
#include <cmath>

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <random>
#include <ctime> 

using namespace std;

bool stop = false;
float timeU = 0.0f;
float rotate = 0.0f;
int screenWidth = 0;
int screenHeight = 0;
bool help = true;
#define PLANE_SIZE 10

const int NUM_VERTICES = 8;
const int NUM_FACES = 6;

/**
 * @brief Maps value x from range in_min/in_max to out_min out_max. This is a linear mapping.
 * 
 * @param x 
 * @param in_min 
 * @param in_max 
 * @param out_min 
 * @param out_max 
 * @return float 
 */
float mapValue(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

/**
 * @brief The structure holding information for each cube.
 * 
 */
struct CubeInfo
{
  /**
   * @brief Velocity vector of cube.
   * 
   */
  glm::vec3 velocity;
  /**
   * @brief Store position on bounce.
   * 
   */
  glm::vec3 oldPosition;
  /**
   * @brief Store time on bounce.
   * 
   */
  float oldTime = 0.0f;

  /**
   * @brief Colors array. A vertice count x 3 array.
   * 
   */
  float** colors;

  /**
   * @brief Construct a new Cube Info object. Random color set.
   * 
   */
  CubeInfo()
  {
    velocity = glm::vec3(0.0f);
    oldPosition = glm::vec3(0.0f);
    colors = new float*[NUM_VERTICES];
    for(int i = 0; i < NUM_VERTICES; i++)
    {
      colors[i] = new float[3];
      colors[i][0] = (float)rand() / (float)RAND_MAX;
      colors[i][1] = (float)rand() / (float)RAND_MAX;
      colors[i][2] = (float)rand() / (float)RAND_MAX;
    }
  }

  /**
   * @brief Increase the lower threshold of the color (increase saturation)
   * 
   * @param in 
   */
  void brightnessAdd(float in)
  {
    for(int i = 0; i < NUM_VERTICES; i++)
    {
      colors[i][0] = mapValue(colors[i][0],0,1,in,1);
      colors[i][1] = mapValue(colors[i][1],0,1,in,1);
      colors[i][2] = mapValue(colors[i][2],0,1,in,1);
    }
  }

  /**
   * @brief Increase the lower threshold of the color with RGB each independently
   * 
   * @param inX 
   * @param inY 
   * @param inZ 
   */
  void brightnessAdd(float inX, float inY, float inZ)
  {
    for(int i = 0; i < NUM_VERTICES; i++)
    {
      colors[i][0] = mapValue(colors[i][0],0,1,inX,1);
      colors[i][1] = mapValue(colors[i][1],0,1,inY,1);
      colors[i][2] = mapValue(colors[i][2],0,1,inZ,1);
    }
  }

};

/**
 * @brief The cubes and planes.
 * 
 */
float planeX = 10;

CubeInfo cube1;
CubeInfo cube2;
CubeInfo cube3;
CubeInfo cube4;

/**
 * @brief The camera position.
 * 
 */
glm::vec4 camOffset;
float zoom;


// The cube has opposite corners at (0,0,0) and (1,1,1), which are black and
// white respectively.  The x-axis is the red gradient, the y-axis is the
// green gradient, and the z-axis is the blue gradient.  The cube's position
// and colors are fixed.
namespace Cube {

GLfloat vertices[NUM_VERTICES][3] = {
  {-0.5, -0.5, -0.5}, {-0.5, -0.5, 0.5}, {-0.5, 0.5, -0.5}, {-0.5, 0.5, 0.5},
  {0.5, -0.5, -0.5}, {0.5, -0.5, 0.5}, {0.5, 0.5, -0.5}, {0.5, 0.5, 0.5}};

GLint faces[NUM_FACES][4] = {
  {1, 5, 7, 3}, {5, 4, 6, 7}, {4, 0, 2, 6},
  {3, 7, 6, 2}, {0, 1, 3, 2}, {0, 4, 5, 1}};

GLfloat vertexColors[NUM_VERTICES][3] = {
  {0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 1.0, 0.0}, {0.0, 1.0, 1.0},
  {1.0, 0.0, 0.0}, {1.0, 0.0, 1.0}, {1.0, 1.0, 0.0}, {1.0, 1.0, 1.0}};

/**
 * @brief Draw a single cube. Set its properties through the CubeInfo struct.
 * 
 * @param cbInfo 
 */
void drawCube(CubeInfo* cbInfo)
{
  glBegin(GL_QUADS);
  glm::vec3 pos = cbInfo->velocity * (timeU - cbInfo->oldTime) + cbInfo->oldPosition;
  /* If cube bounce, reflect on normal  */
  if((pos.x > planeX && cbInfo->velocity.x > 0) || (pos.x < -planeX && cbInfo->velocity.x < 0))
  {
      glm::vec3 normalPlane = glm::vec3((pos.x > 0) * -2 + 1, 0, 0);
      glm::vec3 ref = glm::reflect(cbInfo->velocity, normalPlane);
      cbInfo->velocity = ref;
      cbInfo->oldPosition = pos;
      cbInfo->oldTime = timeU;
  }

  /* Movement and rotation */
  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model, pos);
  model = glm::rotate(model, timeU, glm::vec3(sin(timeU), cos(timeU), sin(timeU / 3)));

  /* Draw each vertex.*/
  for (int i = 0; i < NUM_FACES; i++) {
    for (int j = 0; j < 4; j++) {
      glColor3f(cbInfo->colors[faces[i][j]][0], cbInfo->colors[faces[i][j]][1], cbInfo->colors[faces[i][j]][2]);
  //    cout << "Draw: " << cbInfo->colors[faces[i][j]][0] << ' ' << cbInfo->colors[faces[i][j]][0] << ' ' << cbInfo->colors[faces[i][j]][0] << ' ' << cbInfo->colors[faces[i][j]][0] << endl;

      glm::vec3 original = glm::vec3(vertices[faces[i][j]][0],vertices[faces[i][j]][1],vertices[faces[i][j]][2]);
      glm::vec4 original4 = glm::vec4(original, 1.0f);
      
      glm::vec3 result = model * original4;
      glVertex3f(result.x, result.y, result.z);
    }
  }
  glEnd();
}

/**
 * @brief Helper for rendering strings to window.
 * 
 * @param x 
 * @param y 
 * @param font - Use GLUT fonts.
 * @param string 
 */
void renderBitmapString(float x, float y, void *font, const char* string) {
  glRasterPos2f(x, y);
  int counter = 0;
  char c = string[0];
  while(c != '\0')
  {
    c = string[counter];
    glutBitmapCharacter(font, c);
    counter++;
  }
}

/**
 * @brief The StringDraw class. Draws a string to a window.
 * 
 */
class StringDraw
{
  void* ft;
public:
  StringDraw(void* font)
  {
    ft = font;
    glDisable(GL_TEXTURE_2D); //added this
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0.0, screenWidth, 0.0, screenHeight);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    
  }
  void write(float x, float y, const char* string)
  {
    renderBitmapString(mapValue(x,-1,1,0,screenWidth),mapValue(y,-1,1,0,screenHeight),ft, string);
  }
  void close()
  {
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glEnable(GL_TEXTURE_2D);
  }
};

/**
 * @brief Draw function. Draw the planes, then the axes, then the cubes, then the outside planes.
 * 
 */
void draw() {

  glBegin(GL_QUADS);
    glColor3f(153.0f / 255.0f ,102.0f / 255.0f ,51.0f / 255.0f);
    glVertex3f(-planeX, -PLANE_SIZE, PLANE_SIZE);
    glVertex3f(-planeX, -PLANE_SIZE, -PLANE_SIZE);
    glVertex3f(-planeX, PLANE_SIZE, -PLANE_SIZE);
    glVertex3f(-planeX, PLANE_SIZE, PLANE_SIZE);

    glVertex3f(planeX, PLANE_SIZE, PLANE_SIZE);
    glVertex3f(planeX, PLANE_SIZE, -PLANE_SIZE);
    glVertex3f(planeX, -PLANE_SIZE, -PLANE_SIZE);
    glVertex3f(planeX, -PLANE_SIZE, PLANE_SIZE);

  glEnd();

  /* Draw Axes */
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

    glm::vec3 normal = glm::normalize(glm::vec3(0, -10 * cos(timeU), -30 * sin(timeU)));
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, rotate, normal);
    glm::vec4 result = model * glm::vec4(0.0f, -10 * sin(timeU), 30 * cos(timeU),0.0f);
    result = result + camOffset;

    glm::vec3 camPos = glm::normalize(result);
    glm::vec3 left = glm::normalize(glm::cross(camPos, normal)) * 5.0f;

    glColor3f(0.0f,255.0f,255.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glm::vec3 normDisp = glm::normalize(normal) * 5.0f;
    glVertex3f(normDisp.x, normDisp.y, normDisp.z);

    glColor3f(255.0f,255.0f,0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(left.x, left.y, left.z);

  glEnd();

  /* Draw Cubes */
  drawCube(&cube1);
  drawCube(&cube2);
  drawCube(&cube3);
  drawCube(&cube4);
  
  /* Draw planes */
  glBegin(GL_QUADS);
    glColor3f(153.0f / 255.0f ,102.0f / 255.0f ,51.0f / 255.0f);
    glVertex3f(-planeX, PLANE_SIZE, PLANE_SIZE);
    glVertex3f(-planeX, PLANE_SIZE, -PLANE_SIZE);
    glVertex3f(-planeX, -PLANE_SIZE, -PLANE_SIZE);
    glVertex3f(-planeX, -PLANE_SIZE, PLANE_SIZE);

    glVertex3f(planeX, -PLANE_SIZE, PLANE_SIZE);
    glVertex3f(planeX, -PLANE_SIZE, -PLANE_SIZE);
    glVertex3f(planeX, PLANE_SIZE, -PLANE_SIZE);
    glVertex3f(planeX, PLANE_SIZE, PLANE_SIZE);
  glEnd();

  /* Draw help */
  if(help)
  {
    glColor3f(1.0f,1.0f,1.0f);
    StringDraw sd = StringDraw(GLUT_BITMAP_9_BY_15);
    sd.write(-0.95, 0.9, "Keyboard How-To-Use");
    sd.write(-0.95, 0.85, "s - Stop Animation");
    sd.write(-0.95, 0.80, "c - Continue Animation");
    sd.write(-0.95, 0.75, "r - Rotate Animation");
    sd.write(-0.95, 0.70, "+/- or [] -  Zoom In/Out");
    sd.write(-0.95, 0.65, "u / up-arrow - Move image up (requires it to be stopped first)");
    sd.write(-0.95, 0.60, "d / down-arrow - Move image down (requires it to be stopped first)");
    sd.write(-0.95, 0.55, "left-arrow - Move image left (requires it to be stopped first)");
    sd.write(-0.95, 0.50, "right-arrow - Move image right (requires it to be stopped first)");
    sd.write(-0.95, 0.45, "h - Toggle Help (this menu)");
    sd.write(-0.95, 0.40, "By Benjamin Carter and Josh Canode");
    sd.close();
  }
  
}
}

// Display and Animation. To draw we just clear the window and draw the cube.
// Because our main window is double buffered we have to swap the buffers to
// make the drawing visible. Animation is achieved by successively moving our
// camera and drawing. The function nextAnimationFrame() moves the camera to
// the next point and draws. The way that we get animation in OpenGL is to
// register nextFrame as the idle function; this is done in main().
void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  Cube::draw();
  glFlush();
  glutSwapBuffers();
}

/**
 * @brief Adjust all animation counters. This runs every 1/60 sec.
 * 
 * @param v 
 */
void timer(int v) {
  if(!stop)
  {
    timeU += 0.01;
  }
    glLoadIdentity();
    glm::mat4 model = glm::mat4(zoom);
    glm::vec3 normal = glm::vec3(0, -10 * cos(timeU), -30 * sin(timeU));

    model = glm::rotate(model, rotate, normal);
    glm::vec4 result = model * glm::vec4(0.0f, -10 * sin(timeU), 30 * cos(timeU),0.0f);
    
    result = result + camOffset;

    gluLookAt(result.x,result.y,result.z, camOffset.x, camOffset.y, camOffset.z, normal.x, normal.y, normal.z);
    glutPostRedisplay();
  
  glutTimerFunc(1000/60.0, timer, v);
}

// When the window is reshaped we have to recompute the camera settings to
// match the new window shape.  Set the viewport to (0,0)-(w,h).  Set the
// camera to have a 60 degree vertical field of view, aspect ratio w/h, near
// clipping plane distance 0.5 and far clipping plane distance 40.
void reshape(int w, int h) {
  glViewport(0, 0, w, h);
  screenWidth = w;
  screenHeight = h;
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, GLfloat(w) / GLfloat(h), 0.5, 80.0);
  glMatrixMode(GL_MODELVIEW);
}

// Application specific initialization:  The only thing we really need to do
// is enable back face culling because the only thing in the scene is a cube
// which is a convex polyhedron.
void init() {
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
}

/**
 * @brief Handles keyboard input.
 * 
 * @param key 
 * @param x  - not used
 * @param y - not used
 */
void keyboard(unsigned char key, int x, int y)
{
  if(stop)
  {
    glm::vec3 normal = glm::normalize(glm::vec3(0, -10 * cos(timeU), -30 * sin(timeU)));

   
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, rotate, normal);
    glm::vec4 result = model * glm::vec4(0.0f, -10 * sin(timeU), 30 * cos(timeU),0.0f);
    result = result + camOffset;

    glm::vec3 camPos = glm::normalize(result);
    glm::vec3 left = glm::cross(camPos, normal);

    //std::cout << normal.x << ' ' << normal.y << ' ' << normal.z << ' ' << camPos.x << ' ' << camPos.y << ' ' << camPos.z << ' ' << left.x << ' ' << left.y << ' ' << left.z << std::endl;

    if(key == 'u' || key == 'U' || key == GLUT_KEY_UP)
    {
        camOffset -= glm::vec4(normal, 0.0f) * 0.25f;
    }
    else if(key == 'd' || key == 'D' || key == GLUT_KEY_DOWN)
    {
        camOffset += glm::vec4(normal, 0.0f) * 0.25f;
    }
    else if(key == 'o' || key == 'O' || key == GLUT_KEY_LEFT)
    {
        camOffset -= glm::vec4(left, 0.0f) * 0.25f;
    }
    else if(key == 'p' || key == 'P' || key == GLUT_KEY_RIGHT)
    {
        camOffset += glm::vec4(left, 0.0f) * 0.25f;
    }
  }
//  cout << key << endl;
  if(key == 's' || key == 'S')
  {
    stop = true;
  }
  else if(key == 'c' || key == 'C')
  {
    stop = false;
  }
  else if(key == 'r' || key == 'R')
  {
    rotate += 0.05f;
  }
  else if(key == '[' || key == '-')
  {
    zoom = zoom * 1.01;
  }
  else if(key == ']' || key == '+' || key == '=')
  {
    zoom = zoom / 1.01;
  }
  else if(key == 'h' || key == 'H')
  {
    help = !help;
  }

}

/**
 * @brief Handles special characters. Calls keyboard.
 * 
 * @param key 
 * @param x  - not used
 * @param y - not used
 */
void placeholderKeyboard(int key, int x, int y)
{
  if(key == GLUT_KEY_UP)
  {
    keyboard('u', x, y);
  }
  else if(key == GLUT_KEY_DOWN)
  {
    keyboard('d', x, y);
  }
  else if(key == GLUT_KEY_LEFT)
  {
    keyboard('o', x, y);
  }
  else if(key == GLUT_KEY_RIGHT)
  {
    keyboard('p', x, y);
  }
}

// The usual main for a GLUT application.

int main(int argc, char** argv) {
  srand((unsigned)time(0));
  timeU = 0.0;
  zoom = 1.0;
  rotate = glm::radians(0.0f);

  cube1 = CubeInfo();
  cube1.velocity = glm::vec3(9,0,0);

  cube2 = CubeInfo();
  cube2.velocity = glm::vec3(-4,0,0);
  cube2.oldPosition = glm::vec3(1, 4, 2);

  cube3 = CubeInfo();
  cube3.velocity = glm::vec3(2,0,0);  
  cube3.oldPosition = glm::vec3(-2, -2, -2);
  cube3.brightnessAdd(0.9,0.9,0.1);

  cube4 = CubeInfo();
  cube4.velocity = glm::vec3(0,0,0);
  cube4.brightnessAdd(0.7);


  camOffset = glm::vec4(0.0f);

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(800, 800);
  screenWidth = 800;
  screenHeight = 800;
  glutCreateWindow("The RGB Color Cube");
  glutReshapeFunc(reshape);
  glutTimerFunc(100, timer, 0);
  glutDisplayFunc(display);
  init();
  glutSpecialFunc(placeholderKeyboard);
  glutKeyboardFunc(keyboard);
  glutMainLoop();

}

#endif
