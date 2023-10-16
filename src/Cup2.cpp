/**
 * @file Cup2.h
 * @author Benjamin Carter, Josh Canode.
 * @brief Creates a cup 2 object using the multiPolygon class.
 * @version 0.1
 * @date 2023-10-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "Cup2.h"
#ifndef PI
#define PI           3.14159265358979323846  /* pi */
#endif

Cup2::Cup2()
{
    cupTexture = Texture("cup2.png", 512);
}

void Cup2::postWindowCreate()
{
    cupTexture.setupTexture();
}

void Cup2::draw()
{
    // Create a "circle" face. More like a 20 sided polygon.
    

    glColor3f(CC(223), CC(217), CC(217));

    // then is verticies

    cupTexture.start();    
    glBegin(GL_POLYGON);

        Point center = {581, 333};
        double radiusX = 34;
        double radiusY = 2;

        int precision = 5;
        // double

        for(int r = 0; r > -180; r -= precision) // Half a circle, the top (y is flipped.)
        {
            double rad = (PI * r) / 180.0;
            float x = center.x + radiusX * cos(rad);
            float y = center.y + radiusY * sin(rad);

            cupTexture.markCoord(Window::mapValue(x,531,645,76,426),Window::mapValue(y,463,315,74,474));
            glVertex2f(x,y);
        }

        radiusX = 53;
        radiusY = 14;
        center = {581, 471};
        
        for(int r = 180; r > 0; r -= precision) // Half the circle, the bottom.
        {
            double rad = (PI * r) / 180.0;
            float x = center.x + radiusX * cos(rad);
            float y = center.y + radiusY * sin(rad);

            //cupTexture.markCoord()
            cupTexture.markCoord(Window::mapValue(x,531,645,76,426),Window::mapValue(y,463,315,74,474));
            glVertex2f(x,y);
        }
    
    glEnd();
    cupTexture.stop();

    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    /*
    Point center = {581, 330};
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
    center = {581, 468};
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
    */


    glFlush();
}