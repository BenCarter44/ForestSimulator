#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cstdlib>

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
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(2, -1, 5, 0, 0, 0, 0, 1, 0);

    if (rotating) {
        glRotatef(angle, 0.0f, 0.0f, 1.0f); // Rotate around the z-axis
        angle += 0.2f; // Increment the rotation angle
    } else
    {
        glRotatef(angle, 0.0f, 0.0f, 1.0f); // Rotate around the z-axis
    }

    

    glBegin(GL_TRIANGLES);
    glTexCoord2f(0.5, 1.0);    glVertex2f(-3, 3);
    glTexCoord2f(0.0, 0.0);    glVertex2f(-3, 0);
    glTexCoord2f(1.0, 0.0);    glVertex2f(0, 0);

    glTexCoord2f(4, 8);        glVertex2f(3, 3);
    glTexCoord2f(0.0, 0.0);    glVertex2f(0, 0);
    glTexCoord2f(8, 0.0);      glVertex2f(3, 0);

    glTexCoord2f(5, 5);        glVertex2f(0, 0);
    glTexCoord2f(0.0, 0.0);    glVertex2f(-1.5, -3);
    glTexCoord2f(4, 0.0);      glVertex2f(1.5, -3);
    glEnd();

    glFlush();
    glutSwapBuffers();
}

void moveUp(int direction) {
    switch (direction) {
        case 1: // up arrow
            glTranslatef(0.0f, 0.1f, 0.0f); // move up
            break;
        case 2: // down arrow
            glTranslatef(0.0f, -0.1f, 0.0f); // move down
            break;
        case 3: // right arrow
            glTranslatef(0.1f, 0.0f, 0.0f); // move right
            break;
        case 4: // left arrow
            glTranslatef(-0.1f, 0.0f, 0.0f); // move left
            break;
        default:
            break;
    }
}


void keyboard(unsigned char key, int x, int y) {
    if (key == 's' || key == 'S') {
        rotating = false; // Stop rotation when 's' is pressed
    } else if (key == 'c' || key == 'C') {
        rotating = true; // Continue rotation when 'c' is pressed
    } else if (key == 72) { // up arrow
        moveUp(1);
        // move up
    } else if (key == 80) { // down arrow
        moveUp(2);
        // move down
    } else if (key == 77) { // right arrow
        moveUp(3);
        // move right
    } else if (key == 75) { // left arrow
        moveUp(4);
        // move left
    }   
}



// Initializes GLUT and enters the main loop.
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(520, 390);
    glutCreateWindow("Rotating Textured Triangles");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(display); // Call display function in the idle loop for rotation
    glutKeyboardFunc(keyboard); // Register the keyboard callback

    glutMainLoop();
    return 0;
}
