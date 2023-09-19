#ifndef WINDOW_H
#define WINDOW_H

#include "WindowManager.h"

class Window
{
    friend class WindowManager;
private:
    int sizeX;
    int sizeY;
    const char[] title;

public:
   Window(const char[] title);  

};


#endif