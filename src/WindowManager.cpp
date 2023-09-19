#include "WindowManager.h"

WindowManager::WindowManager(int &argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
}
