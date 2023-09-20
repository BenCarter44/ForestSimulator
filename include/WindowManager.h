#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include <GL/glut.h>
#include "Window.h"

using namespace std;




class WindowManager
{
private:
  static Window* myWindow;

public:
    static void mainDisplay();

    WindowManager(int &argc, char** argv);
    void setWindow(Window* w);
    void mainLoop();

};


#endif