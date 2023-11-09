/**
 * @file CheckeredTriangles.cpp
 * @author Josh Canode and Benjamin Carter
 * @brief A checkered triangle "windmill". Camera position is movable.
 * @version 0.1
 * @date 2023-11-08
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifdef PART1BUILD

#include <GL/glut.h>
#include <cstdio>
#include <stdio.h>
#include <iostream>

using namespace std;

// Global variables
    float x_pos = 0;
    float y_pos = 0;
    float zoom = 1.0;


bool rotating = true; // Flag to control rotation


// Define a 2 x 2 red and yellow checkered pattern using RGB colors.
#define red {0xff, 0x00, 0x00}
#define yellow {0xff, 0xff, 0x00}
#define magenta {0xff, 0, 0xff}
GLubyte texture[][3] = {
    red, yellow,

    yellow, red,
};



// Rotation angle
float angle = 0.0f;


// Fixes up camera and remaps texture when window reshaped.
void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(80, GLfloat(width) / height, 1, 40);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(3, -1, 5, 0, 0, 0, 0, 1, 0);
    glEnable(GL_TEXTURE_2D);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D,
        0,                    // level 0
        3,                    // use only R, G, and B components
        2, 2,                 // texture has 2x2 texels
        0,                    // no border
        GL_RGB,               // texels are in RGB format
        GL_UNSIGNED_BYTE,     // color components are unsigned bytes
        texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

// Draws three textured triangles.  Each triangle uses the same texture,
// but the mappings of texture coordinates to vertex coordinates is
// different in each triangle.
void updateAngle(int a)
{
    if(rotating){
        angle += 0.35f;
    }
    glutTimerFunc(5, updateAngle, 0);

}

void display() {

    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 5 * zoom, 0, 0, 0, 0, 1, 0);

 
        glTranslatef(x_pos, y_pos, 0.0f); // Translate to the center of the triangle
        glRotatef(angle, 0.0f, 0.0f, 1.0f); // Rotate around the z-axis
    
    
    glColor3f(1.0f,1.0f,1.0f);
    glBegin(GL_TRIANGLES);
    glTexCoord2f(0.5 , 1.0 );    glVertex2f(-3 , 3 );
    glTexCoord2f(0.0 , 0.0 );    glVertex2f(-3 , 0 );
    glTexCoord2f(1.0 , 0.0 );    glVertex2f(0 , 0 );

    glTexCoord2f(4 , 8 );        glVertex2f(3 , 3 );
    glTexCoord2f(0.0 , 0.0 );    glVertex2f(0 , 0 );
    glTexCoord2f(8 , 0.0 );      glVertex2f(3 , 0 );

    glTexCoord2f(5 , 5 );        glVertex2f(0 , 0 );
    glTexCoord2f(0.0 , 0.0 );    glVertex2f(-1.5 , -3 );
    glTexCoord2f(4 , 0.0 );      glVertex2f(1.5 , -3 );
    glEnd();


    glFlush();
    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 's':
        case 'S':
        case 'p':
            rotating = false; // Stop rotation when 's' is pressed
            break;
        case 'c':
        case 'C':
            rotating = true; // Continue rotation when 'c' is pressed
            break;
        case '-':
        case '_':
            zoom = zoom / 0.9;
            break;
        case '+':
        case '=':
            zoom = zoom / 1.1;
            break;
    }
}

void specialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP: // Up arrow key
            y_pos += 0.5f;
            break;
        case GLUT_KEY_LEFT: // Left arrow key
            x_pos -= 0.5f;
            break;
        case GLUT_KEY_DOWN: // Down arrow key
            y_pos -= 0.5f;
            break;
        case GLUT_KEY_RIGHT: // Right arrow key
            x_pos += 0.5f;
            break;
    }
}



// Initializes GLUT and enters the main loop.
int main(int argc, char** argv) {
    std::cout << "Checkered Triangles - Josh Canode and Benjamin Carter\n=============================" << std::endl;
    std::cout << "Press s to stop animation\nPress c to continue animation\nPress - to zoom out\nPress + to zoom in\nUse arrow keys to move object up/down/left/right" << std::endl; 
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(520, 390);
    glutCreateWindow("Rotating Textured Triangles");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(display); // Call display function in the idle loop for rotation
    glutKeyboardFunc(keyboard); // Register the keyboard callback
    glutSpecialFunc(specialKeys);
    glutTimerFunc(100, updateAngle, 0); 

    glutMainLoop();
    return 0;
}
#endif