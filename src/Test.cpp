#include "Test.h"

#ifndef PI
#define PI           3.14159265358979323846  /* pi */
#endif

Test::Test()
{

}

void Test::draw()
{
    glColor3f(0.0f,0.0f,0.0f);
    Point center = {200.0, 200.0};
    Point newPoint = {250.0,200.0};

    glBegin(GL_LINE_STRIP);
        glVertex2f(center.x,center.y);
        glVertex2f(newPoint.x,newPoint.y);
        newPoint.rotate(45.0,center);
        glVertex2f(newPoint.x,newPoint.y);
        std::cout << newPoint.x << ' ' << newPoint.y << endl;
        newPoint.rotate(90.0,center);
        glVertex2f(newPoint.x,newPoint.y);
        std::cout << newPoint.x << ' ' << newPoint.y << endl;
        newPoint.rotate(135.0,center);
        glVertex2f(newPoint.x,newPoint.y);
        std::cout << newPoint.x << ' ' << newPoint.y << endl;
        newPoint.rotate(180.0,center);
        glVertex2f(newPoint.x,newPoint.y);
        std::cout << newPoint.x << ' ' << newPoint.y << endl;
        newPoint.rotate(225.0,center);
        glVertex2f(newPoint.x,newPoint.y);
        std::cout << newPoint.x << ' ' << newPoint.y << endl;
        newPoint.rotate(270.0,center);
        glVertex2f(newPoint.x,newPoint.y);
        std::cout << newPoint.x << ' ' << newPoint.y << endl;
        newPoint.rotate(315.0,center);
        glVertex2f(newPoint.x,newPoint.y);
        std::cout << newPoint.x << ' ' << newPoint.y << endl;
        newPoint.rotate(360.0,center);
        glVertex2f(newPoint.x,newPoint.y);
        std::cout << newPoint.x << ' ' << newPoint.y << endl;
    glEnd();



    glFlush();
}