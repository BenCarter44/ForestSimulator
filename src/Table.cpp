#include "Table.h"

float cc(float x)
{
    return x / 255.0f;
}

Table::Table()
{

}

void Table::draw()
{
    glClearColor(cc(202),cc(192),cc(182),0.0f);
    cout << "glClear(GL_COLOR_BUFFER_BIT);\n";
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    cout << "glBegin(GL_POLYGON);\n";

    int topPointsX[] = {110, 49, 979, 583};
    int topPointsY[] = {424, 607, 507, 408};
    
    int oldPointsY[4];

    glBegin(GL_POLYGON);
        glColor3f(cc(200),cc(165),cc(135));
        for(int i = 0; i < 4; i++)
        {
            glVertex2f(topPointsX[i],topPointsY[i]);
        }
    glEnd();
    
    
    // translate down by spacing!
    int spacing = 659 - 607;

    for(int i = 0; i < 4; i++)
    {
        std::cout << topPointsX[i] << ' ' << Window::mapValue(topPointsX[i],49.0f,979.0f,56.0f,35.0f) << endl;
        oldPointsY[i] = topPointsY[i];
        topPointsY[i] = topPointsY[i] + Window::mapValue(topPointsX[i],49,979,spacing,35);

    }

    int bordersX[] = {topPointsX[0],topPointsX[1],topPointsX[1],topPointsX[0]};
    int bordersY[] = {topPointsY[0],topPointsY[1],oldPointsY[1],oldPointsY[0]};
    
    glBegin(GL_POLYGON);
        glColor3f(cc(12),cc(10),cc(11));
        for(int i = 0; i < 4; i++)
        {
            glVertex2f(bordersX[i],bordersY[i]);
        }
    glEnd();

    int bordersX_2[] = {topPointsX[2],topPointsX[3],topPointsX[3],topPointsX[2]};
    int bordersY_2[] = {topPointsY[2],topPointsY[3],oldPointsY[3],oldPointsY[2]};

    glBegin(GL_POLYGON);
        glColor3f(cc(12),cc(10),cc(11));
        for(int i = 0; i < 4; i++)
        {
            glVertex2f(bordersX_2[i],bordersY_2[i]);
        }
    glEnd();

    glBegin(GL_POLYGON);
        glColor3f(cc(12),cc(10),cc(11));
        for(int i = 0; i < 4; i++)
        {
            glVertex2f(topPointsX[i],topPointsY[i]);
        }
    glEnd();

    // take above and translate down to 48,660

    // take the legs and translate/scale. (145-56)   (971 - 908)

    int legPointsX[] = {56, 150, 150, 56};
    int legPointsY[] = {645, 645, 750, 750};

    glBegin(GL_POLYGON);
        glColor3f(cc(12),cc(10),cc(11));
        for(int i = 0; i < 4; i++)
        {
            glVertex2f(legPointsX[i],legPointsY[i]);
        }
    glEnd();

    int leftSideLegX = 904;
    int rightSideLegX = 975;

    int height = 530;

    glBegin(GL_POLYGON);
        glVertex2f(leftSideLegX,height);
        glVertex2f(rightSideLegX,height);
        glVertex2f(rightSideLegX,750);
        glVertex2f(leftSideLegX,750);
    glEnd();

    int bottomBarX[] = {525, 936, 933, 550};
    int bottomBarY[] = {750, 670, 710, 780};

    glBegin(GL_POLYGON);
        glColor3f(cc(12),cc(10),cc(11));
        for(int i = 0; i < 4; i++)
        {
            glVertex2f(bottomBarX[i],bottomBarY[i]);
        }
    glEnd();


    Point pointsList[8] = {
    {110, 224},
    {49, 407},
    {979, 307},
    {583, 208},
    {110, 172},
    {49, 355},
    {979, 255},
    {583, 156}
    };

    Polygon p = Polygon(pointsList,8);
    
    Face** colorFaces = p.getColorFaces();
    int r = 0;
    int g = 0;
    int b = 0;
    for(int f = 0; f < p.getNumberFaces(); f++)
    {
      cout << "AREA: " << Polygon::getArea(colorFaces[f]) << endl;
      colorFaces[f]->r = r;
      colorFaces[f]->g = g;
      colorFaces[f]->b = b;
      r += 40;
    }

    p.draw();



    cout << "glFlush();\n";
    glFlush();
}