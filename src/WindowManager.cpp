#include "WindowManager.h"

WindowManager::WindowManager(int &argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
}

void WindowManager::setWindow(Window* w)
{
    
    glutInitWindowSize(w->getSizeX(), w->getSizeY());
    glutInitWindowPosition(w->getStartX(), w->getStartY());
    glutCreateWindow(w->getTitle());
     // basically. do 3D.  https://registry.khronos.org/OpenGL-Refpages/gl4/html/glEnable.xhtml
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(WindowManager::mainDisplay);
    
    myWindow = w;
}

void WindowManager::mainLoop()
{
    glutMainLoop();
}

void WindowManager::mainDisplay()
{
    myWindow->display();
}