/**
 * @file stickyNotes.cpp
 * @author Benjamin Carter, Josh Canode.
 * @brief Creates bule, green, and red stickynotes using the multiPolygon class.
 * @version 0.1
 * @date 2023-10-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "stickyNotes.h"


stickyNotes::stickyNotes()
{

}

void stickyNotes::draw()
{
    // green
    Point greenTop[4] = {
        {298, 557},
        {167, 546},
        {244, 516},
        {360, 528}
    };
    AnchorFace greenTopFace = AnchorFace(greenTop, 4);
    greenTopFace.setColor(52,235,137);

    Point greenTopLower[4] = {
        {296, 584},
        {165, 566},
        {248, 528},
        {362, 542}
    };
    AnchorFace greenTopLowFace = AnchorFace(greenTopLower, 4);
    greenTopLowFace.setColor(200,164,132);

    MultiPolygon green = MultiPolygon(&greenTopFace, &greenTopLowFace);
    Face** walls = green.getColorFaces();

    //walls = green.getColorFaces();
    for(int i = 0; i < green.getColorFacesNum(); i++)
    {
       walls[i]->setColor(52,235,137);
    }

    
    // blue
    Point blueTop[4] = {
        {473, 534},
        {382, 514},
        {450, 495},
        {546, 512}
    };
    AnchorFace blueTopFace = AnchorFace(blueTop, 4);
    blueTopFace.setColor(52, 192, 235);

    Point blueTopLower[4] = {
        {474, 551},
        {377, 529},
        {452, 505},
        {544, 525}
    };
    AnchorFace blueTopLowFace = AnchorFace(blueTopLower, 4);
    blueTopLowFace.setColor(52, 192, 235);

    MultiPolygon blue = MultiPolygon(&blueTopFace, &blueTopLowFace);
    
    walls = blue.getColorFaces();
    for(int i = 0; i < blue.getColorFacesNum(); i++)
    {
       walls[i]->setColor(52, 192, 235);
    }   


    // red
    Point redTop[4] = {
        {490, 505},
        {466, 485},
        {550, 476},
        {591, 503}
    };
    AnchorFace redTopFace = AnchorFace(redTop, 4);
    redTopFace.setColor(235,58,52);

    Point redTopLower[4] = {
        {490, 492},
        {467, 470},
        {554, 470},
        {591, 490}
    };
    AnchorFace redTopLowFace = AnchorFace(redTopLower, 4);
    redTopLowFace.setColor(235,58,52);

    MultiPolygon red = MultiPolygon(&redTopFace, &redTopLowFace);
    
    walls = red.getColorFaces();
    for(int i = 0; i < red.getColorFacesNum(); i++)
    {
       walls[i]->setColor(235,58,52);
    }   




    green.draw();
    blue.draw();
    red.draw();
    cout << "glFlush();\n";
    glFlush();
}