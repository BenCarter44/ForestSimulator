/****
 * Graphics Development Workflow for OpenGL
 * 
 * 
*/

using namespace std;

#include "WindowManager.h"
#include "Window.h"

int main(int argc, char** argv)
{
    WindowManager manager = WindowManager(argc, argv);
    Window win = Window("My title", 200, 180);
    manager.setWindow(&win);

    DisplayObject basicTriangle = DisplayObject();

    win.addObject(&basicTriangle);

    manager.mainLoop();

    return 0;
}
