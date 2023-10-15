/**
 * @file CatchPhrase.cpp
 * @author Ben Carter, Josh Canode
 * @brief This creates the CatchPhrase object
 * @version 0.1
 * @date 2023-10-08
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "CatchPhrase.h"

#ifndef PI
#define PI           3.14159265358979323846  /* pi */
#endif

CatchPhrase::CatchPhrase()
{
    topTexture = Texture("catchPhraseSide.png",1024);
}
void CatchPhrase::postWindowCreate()
{
    topTexture.setupTexture();
}
void CatchPhrase::draw()
{

// 184, 478    X distance: 110
// 409, 461

// 325, 495    Y distance: 32
// 283, 451

// center: 300, 471


    // Create a "circle" face. More like a 20 sided polygon.

    Point center = {303, 469};
    double radius = 5;

    int precision = 5;
    Point circle[360 / precision];
    Point circleTx[360 / precision];
    // double
    int counter = 0;
    for(int r = 0; r < 360; r += precision) // 15deg precision.
    {
        double rad = (PI * r) / 180.0;
        circle[counter] = {center.x + 110 * cos(rad), center.y + 32 * sin(rad)};

        circle[counter].x = Window::mapValue(circle[counter].x,193.0f,413.0f,180.0f,410.0f); // scaling and rotation
        circle[counter].y = Window::mapValue(circle[counter].y,437.0f,501.0f,450.0f,495.0f);

        circle[counter].y = circle[counter].y - 4.75f * Window::mapValue(circle[counter].x,180.0f,410.0f,-1.0f,1.0f);

        circleTx[counter].x = Window::mapValue(circle[counter].x,180.0f,410.0f,40.0f,960.0f);
        circleTx[counter].y = Window::mapValue(circle[counter].y,450.0f,495.0f,581.0f,400.0f);

        std::cout << "CIRCLE" << circle[counter].x << ' '  << circle[counter].y << '\n';
        counter++;
    }

    center.y = center.y + 32;
    Point circle2[360 / precision];
    // double
    counter = 0;
    for(int r = 0; r < 360; r += precision) // 15deg precision.
    {
        double rad = (PI * r) / 180.0;
        circle2[counter] = {center.x + 110 * cos(rad), center.y + 32 * sin(rad)};

        circle2[counter].x = Window::mapValue(circle2[counter].x,193.0f,413.0f,180.0f,410.0f);
        circle2[counter].y = Window::mapValue(circle2[counter].y,437.0f,501.0f,450.0f,495.0f);

        circle2[counter].y = circle2[counter].y - 4.75f * Window::mapValue(circle2[counter].x,180.0f,410.0f,-1.0f,1.0f);

        counter++;
    }

    AnchorFace top = AnchorFace(circle, 360 / precision);
  //  top.setColor(84, 87, 120);
    top.setColor(255, 255, 255);
    top.setTexture(&topTexture, circleTx);
    
    AnchorFace bottom = AnchorFace(circle2, 360 / precision);
    bottom.setColor(11,11,9);
    MultiPolygon pen = MultiPolygon(&top, &bottom);
    Face** walls = pen.getColorFaces();
    for(int x = 0; x < pen.getColorFacesNum(); x++)
    {
        float grad = Window::mapValue((float)((x - 1) % pen.getColorFacesNum()) , 0.0f, (float)pen.getColorFacesNum(), 0.0f, 2.0f);
        float color[3];
        if(grad < 0.5f)
        {
            Window::mixColor(color, grad, 41,33,22,82,83,85);
        }
        else
        {
            Window::mixColor(color, 1.0 - grad, 41,33,22, 82,83,85);
        }
        if(x < 17 / precision )
        {
            Window::mixColor(color, (float)((float)x / (17 / precision)),70.0f,116.0f,113.0f, 90.0f, 136.0f, 133.0f);
        }
        walls[x]->setColor((uint8_t)color[0],(uint8_t)color[1], (uint8_t)color[2]);
    }

    pen.draw();



    glFlush();
}