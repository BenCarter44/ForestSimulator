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
        {360, 528},
        {298, 557},
        {167, 546},
        {243, 517},
    };
    AnchorFace greenTopFace = AnchorFace(greenTop, 4);
    greenTopFace.setColor(120,183,138);

    Point greenTopLower[4] = {
        {362, 542},
        {297, 578},
        {165, 566},
        {248, 528}
    };
    AnchorFace greenTopLowFace = AnchorFace(greenTopLower, 4);
    greenTopLowFace.setColor(79,147,98);

    MultiPolygon green = MultiPolygon(&greenTopFace, &greenTopLowFace);
    Face** walls = green.getColorFaces();

    //walls = green.getColorFaces();
    for(int i = 0; i < green.getColorFacesNum(); i++)
    {
        if( i % 2 != 0)
        {
            walls[i]->setColor(65,128,99);
        }
        else
        {
           walls[i]->setColor(61,97,69); 
        }
    }

    
    // blue
    Point blueTop[4] = {
        {546, 512},
        {473, 534},
        {382, 514},
        {450, 495}
    };
    AnchorFace blueTopFace = AnchorFace(blueTop, 4);
    blueTopFace.setColor(126, 177, 206);

    Point blueTopLower[4] = {
        {544, 525},
        {474, 551},
        {377, 529},
        {452, 505}
    };
    AnchorFace blueTopLowFace = AnchorFace(blueTopLower, 4);
    blueTopLowFace.setColor(52, 192, 235);

    MultiPolygon blue = MultiPolygon(&blueTopFace, &blueTopLowFace);
    
    walls = blue.getColorFaces();
    for(int i = 0; i < blue.getColorFacesNum(); i++)
    {
        if( i % 2 == 0)
        {
            walls[i]->setColor(60,97,113);
        }
        else
        {
           walls[i]->setColor(74,133,165); 
        }
    }


    // red
    Point redTop[4] = {
        {591, 490},
        {490, 492},
        {467, 470},
        {554, 470}
    };
    AnchorFace redTopFace = AnchorFace(redTop, 4);
    redTopFace.setColor(225,104,93);

    Point redTopLower[4] = {
        {591, 503},
        {490, 505},
        {466, 485},
        {550, 476}
    };
    AnchorFace redTopLowFace = AnchorFace(redTopLower, 4);
    redTopLowFace.setColor(225,104,93);

    MultiPolygon red = MultiPolygon(&redTopFace, &redTopLowFace);
    
    walls = red.getColorFaces();
    for(int i = 0; i < red.getColorFacesNum(); i++)
    {
        if( i % 2 != 0)
        {
            walls[i]->setColor(146,51,45);
        }
        else
        {
           walls[i]->setColor(173,91,80); 
        }
    } 




    green.draw();
    blue.draw();
    red.draw();
    cout << "glFlush();\n";
    glFlush();
}