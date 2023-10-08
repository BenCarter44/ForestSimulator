#include "Orange.h"

#ifndef PI
#define PI           3.14159265358979323846  /* pi */
#endif

Orange::Orange()
{

}

void Orange::draw()
{
    glColor3f(209 / 255.0f, 121 / 255.0f, 49 / 255.0f);

    // then is verticies

    Point orangePoints[] = {
        {488,249},
        {478,250},
        {469,252},
        {461,256},
        {455,262},
        {450,267},
        {446,275},
        {445,282},
        {444,291},
        {443,301},
        {445,311},
        {449,323},
        {459,333},
        {467,333},
        {508,334},
        {512,330},
        {517,325},
        {522,317},
        {526,309},
        {528,298},
        {528,284},
        {524,274},
        {518,263},
        {511,257},
        {502,252},
        {492,250},
        {484,262}
    };
    glBegin(GL_TRIANGLE_FAN);
    for(int i = 0; i < 27; i++)
    {
        glVertex2f(orangePoints[i].x,orangePoints[i].y);
    }
    glEnd();



    glFlush();
}