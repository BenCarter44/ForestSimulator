#include "Cup3.h"

#ifndef PI
#define PI           3.14159265358979323846  /* pi */
#endif

Cup3::Cup3()
{

}

void Cup3::draw()
{
    // Create a "circle" face. More like a 20 sided polygon.

    Point center = {660, 332};
    double radiusX = 34;
    double radiusY = 1;

    int precision = 5;
    Point circle[360 / precision];
    // double
    int counter = 0;
    for(int r = 0; r < 360; r += precision) // 15deg precision.
    {
        double rad = (PI * r) / 180.0;
        circle[counter] = {
            center.x + radiusX * cos(rad),
            center.y + radiusY * sin(rad)
        };
        // 
        std::cout << "Ellipse" << circle[counter].x << ' '  << circle[counter].y << '\n';
        counter++;
    }
    radiusX = 51;
    radiusY = 14;
    center = {660, 472};
    Point circle2[360 / precision];
    // double
    counter = 0;
    for(int r = 0; r < 360; r += precision) // 15deg precision.
    {
        double rad = (PI * r) / 180.0;
        //circle2[counter] = {center.x + cos(rad) * radius, center.y + sin(rad) * radius};
        circle2[counter] = {
            center.x + radiusX * cos(rad),
            center.y + radiusY * sin(rad)
        };
        counter++;
    }

    AnchorFace top = AnchorFace(circle, 360 / precision);
    top.setColor(76, 69, 61);
    AnchorFace bottom = AnchorFace(circle2, 360 / precision);
    bottom.setColor(145,135,125);
    MultiPolygon pen = MultiPolygon(&top, &bottom);
    Face** walls = pen.getColorFaces();
    for(int x = 0; x < pen.getColorFacesNum(); x++)
    {
        float grad = Window::mapValue((float)x, 0.0f, (float)pen.getColorFacesNum(), 1.0f, 0.0f);
        float color[3];
        Window::mixColor(color, grad, 33,29,22,182,172,160);
        walls[x]->setColor((uint8_t)color[0],(uint8_t)color[1], (uint8_t)color[2]);
    }

    pen.draw();



    glFlush();
}