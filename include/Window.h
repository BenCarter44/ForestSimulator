#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glut.h>
#include "DisplayObject.h"
#include <vector>
using std::vector;
using namespace std;

class Window
{
    
private:
    int sizeX;
    int sizeY;
    int startX;
    int startY;
    const char* title;
    vector<DisplayObject*> allObjects;

public:
    Window();  
    Window(const char* titl);  
    Window(const char* title, int inX, int inY);
    Window(int inX, int inY);
    void setStartX(int x);
    void setStartY(int y);
    void addObject(DisplayObject* disp);
    void display();
    
    int getSizeX();
    int getSizeY();
    int getStartX();
    int getStartY();

    const char* getTitle();
};


#endif