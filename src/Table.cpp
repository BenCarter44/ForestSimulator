#include "Table.h"


#define CC(ARG) (ARG/255.0f)

Table::Table()
{

}

void Table::draw()
{
    glClearColor(CC(202),CC(192),CC(182),0.0f);
    cout << "glClear(GL_COLOR_BUFFER_BIT);\n";
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    cout << "glBegin(GL_POLYGON);\n";

    // black border
    Point blackTop[4] = {
        {48, 610},
        {110, 425},
        {583, 409},
        {979, 507}
    };
    AnchorFace top = AnchorFace(blackTop, 4);
    top.setColor(76,71,68);

    Point blackTopLower[4] = {
        {48, 659},
        {108, 442},
        {581, 420},
        {977, 538}
    };
    AnchorFace bottom = AnchorFace(blackTopLower, 4);
    bottom.setColor(16,15,13);

    MultiPolygon blackTableBorder = MultiPolygon(&top, &bottom);

    Face** walls = blackTableBorder.getColorFaces();
    for(int i = 0; i < blackTableBorder.getColorFacesNum(); i++)
    {
        walls[i]->setColor(15, 14, 12);
    }

    // wood
    Point woodTop[4] = {
        {88, 595},
        {125, 426},
        {600, 411},
        {949, 504}
    };
    AnchorFace woodTopFace = AnchorFace(woodTop, 4);
    woodTopFace.setColor(200,164,132);

    Point woodTopLower[4] = {
        {86, 624},
        {126, 436},
        {603, 425},
        {949, 524}
    };
    AnchorFace woodTopLowFace = AnchorFace(woodTopLower, 4);
    woodTopLowFace.setColor(200,164,132);

    MultiPolygon wood = MultiPolygon(&woodTopFace, &woodTopLowFace);

    walls = wood.getColorFaces();
    for(int i = 0; i < wood.getColorFacesNum(); i++)
    {
        walls[i]->setColor(15, 14, 12);
    }


    // leg1
    Point leg1Pts[4] = {
        {133, 647},
        {58, 649},
        {64, 627},
        {146, 630}

    };
    AnchorFace leg1AF = AnchorFace(leg1Pts, 4);
    leg1AF.setColor(18,16,17);

    Point leg1PtsB[4] = {
        {136, 750},
        {58, 750},
        {64, 750},
        {146, 750}

    };
    AnchorFace leg1BF = AnchorFace(leg1PtsB, 4);
    leg1BF.setColor(18,16,17);

    MultiPolygon leg1 = MultiPolygon(&leg1AF, &leg1BF);

    walls = leg1.getColorFaces();
    walls[0]->setColor(26, 21, 18);
    walls[1]->setColor(0, 255, 0);
    walls[2]->setColor(18, 18, 18);
    walls[3]->setColor(18, 18, 18);


    // leg2
    Point leg2Pts[4] = {
        {908, 546},
        {950, 532},
        {972, 540},
        {946, 544}

    };
    AnchorFace leg2AF = AnchorFace(leg2Pts, 4);
    leg2AF.setColor(18,16,17);

    Point leg2PtsB[4] = {
        {897, 750},
        {938, 750},
        {958, 750},
        {930, 750}

    };
    AnchorFace leg2BF = AnchorFace(leg2PtsB, 4);
    leg2BF.setColor(18,16,17);

    MultiPolygon leg2 = MultiPolygon(&leg2AF, &leg2BF);

    walls = leg2.getColorFaces();
    walls[0]->setColor(13, 14, 9);
    walls[1]->setColor(31, 28, 21);
    walls[2]->setColor(0, 0, 255);
    walls[3]->setColor(255, 0, 0);


    // leg3
    Point leg3Pts[4] = {
        {560, 590},
        {581, 587},
        {590, 587},
        {571, 589}

    };
    AnchorFace leg3AF = AnchorFace(leg3Pts, 4);
    leg3AF.setColor(17,16,12);

    Point leg3PtsB[4] = {
        {556, 750},
        {573, 749},
        {584, 750},
        {567, 750}
    };
    AnchorFace leg3BF = AnchorFace(leg3PtsB, 4);
    leg3BF.setColor(17,16,12);

    MultiPolygon leg3 = MultiPolygon(&leg3AF, &leg3BF);

    walls = leg3.getColorFaces();
    walls[0]->setColor(16, 15, 11);
    walls[1]->setColor(31, 28, 21);
    walls[2]->setColor(0, 0, 255);
    walls[3]->setColor(255, 0, 0);

     // bar1
    Point bar1Pts[4] = {
        {935, 671},
        {570, 750},
        {530, 750},
        {920, 666},
    };
    AnchorFace bar1AF = AnchorFace(bar1Pts, 4);
    bar1AF.setColor(17,16,12);

    Point bar1PtsB[4] = {
        {932, 705},
        {719, 750},
        {685, 750},
        {901, 702}
    };
    AnchorFace bar1BF = AnchorFace(bar1PtsB, 4);
    bar1BF.setColor(17,16,12);

    MultiPolygon bar1 = MultiPolygon(&bar1AF, &bar1BF);

    walls = bar1.getColorFaces();
    walls[0]->setColor(20, 19, 15);
    walls[1]->setColor(31, 28, 21);
    walls[2]->setColor(0, 0, 255);
    walls[3]->setColor(255, 0, 0);

    // bar2
    Point bar2Pts[4] = {
        {902, 678},
        {691, 573},
        {731, 569},
        {904, 649},
    };
    AnchorFace bar2AF = AnchorFace(bar2Pts, 4);
    bar2AF.setColor(16,12,9);

    Point bar2PtsB[4] = {
        {914, 671},
        {703, 572},
        {735, 568},
        {904, 643}
    };
    AnchorFace bar2BF = AnchorFace(bar2PtsB, 4);
    bar2BF.setColor(17,16,12);

    MultiPolygon bar2 = MultiPolygon(&bar2AF, &bar2BF);

    walls = bar2.getColorFaces();
    walls[0]->setColor(35, 32, 25);
    walls[1]->setColor(31, 28, 21);
    walls[2]->setColor(35, 32, 25);
    walls[3]->setColor(255, 0, 0);


    // support1
    Point support1Pts[4] = {
        {449, 608},
        {455, 608},
        {476, 605},
        {470, 602},
    };
    AnchorFace support1AF = AnchorFace(support1Pts, 4);
    support1AF.setColor(16,12,9);

    Point support1PtsB[4] = {
        {446, 750},
        {451, 750},
        {472, 750},
        {464, 750}
    };
    AnchorFace support1BF = AnchorFace(support1PtsB, 4);
    support1BF.setColor(17,16,12);

    MultiPolygon support1 = MultiPolygon(&support1AF, &support1BF);

    walls = support1.getColorFaces();
    walls[0]->setColor(33, 28, 24);
    walls[1]->setColor(9, 11, 8);
    walls[2]->setColor(0, 255, 0);
    walls[3]->setColor(255, 0, 0);


    // support2
    Point support2Pts[4] = {
        {606, 587},
        {615, 586},
        {633, 584},
        {626, 582},
    };
    AnchorFace support2AF = AnchorFace(support2Pts, 4);
    support2AF.setColor(16,12,9);

    Point support2PtsB[4] = {
        {600, 734},
        {609, 744},
        {625, 739},
        {618, 731}
    };
    AnchorFace support2BF = AnchorFace(support2PtsB, 4);
    support2BF.setColor(17,16,12);

    MultiPolygon support2 = MultiPolygon(&support2AF, &support2BF);

    walls = support2.getColorFaces();
    walls[0]->setColor(33, 28, 24);
    walls[1]->setColor(9, 11, 8);
    walls[2]->setColor(0, 255, 0);
    walls[3]->setColor(255, 0, 0);

    // support3
    Point support3Pts[4] = {
        {740, 564},
        {753, 564},
        {765, 562},
        {758, 563},
    };
    AnchorFace support3AF = AnchorFace(support3Pts, 4);
    support3AF.setColor(16,12,9);

    Point support3PtsB[4] = {
        {731, 705},
        {743, 715},
        {756, 712},
        {746, 704}
    };
    AnchorFace support3BF = AnchorFace(support3PtsB, 4);
    support3BF.setColor(17,16,12);

    MultiPolygon support3 = MultiPolygon(&support3AF, &support3BF);

    walls = support3.getColorFaces();
    walls[0]->setColor(33, 28, 24);
    walls[1]->setColor(9, 11, 8);
    walls[2]->setColor(0, 255, 0);
    walls[3]->setColor(255, 0, 0);

    // support4
    Point support4Pts[4] = {
        {764, 566},
        {775, 565},
        {782, 564},
        {777, 562},
    };
    AnchorFace support4AF = AnchorFace(support4Pts, 4);
    support4AF.setColor(16,12,9);

    Point support4PtsB[4] = {
        {761, 584},
        {773, 588},
        {781, 590},
        {773, 584}
    };
    AnchorFace support4BF = AnchorFace(support4PtsB, 4);
    support4BF.setColor(17,16,12);

    MultiPolygon support4 = MultiPolygon(&support4AF, &support4BF);

    walls = support4.getColorFaces();
    walls[0]->setColor(13, 12, 8);
    walls[1]->setColor(23, 22, 17);
    walls[2]->setColor(0, 255, 0);
    walls[3]->setColor(255, 0, 0);


    wood.draw();
    blackTableBorder.draw();
    leg1.draw();
    support1.draw();
    support2.draw();
    support3.draw();
    bar1.draw();
    leg2.draw();
    support4.draw();
    bar2.draw();
    
    leg3.draw();
    cout << "glFlush();\n";
    glFlush();
}