/**
 * @file Window.h
 * @author your name (you@domain.com)
 * @brief This file defines the Window class. \
 * This class acts as a "static class" in a way, as it changes static values \
 * (as only one window supported at a time.)
 * 
 * @version 0.1
 * @date 2023-09-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glut.h>
#include "DisplayObject.h"

// https://stackoverflow.com/questions/4576282/preprocessor-macros-how-to-insert-arguments

/* DEFINE DEBUG_WIN_CMD to get cout's of the glut commands to console. */
#define DEBUG_WIN_CMD

#ifdef DEBUG_WIN_CMD
#define DEBUG_WIN(ARG) (cout << #ARG";\n")
#include <iostream>
#else
#define DEBUG_WIN(ARG) while(false)
#endif

#include <vector>
using std::vector;
using namespace std;

class Window
{
private:
    /**
     * @brief Static values of the window. Static as these are window-agnostic
    */
    static int sizeX;
    static int sizeY;
    static int startX;
    static int startY;
    static const char* title;

    /**
     * @brief A vector to hold the objects in the window. Each object is a DisplayObject
    */
    static vector<DisplayObject*> allObjects;

public:
    /**
     * @brief Construct a new Window object
     * 
     */
    Window();

    /**
     * @brief Construct a new Window object
     * 
     * @param titl - The title of the window
     * 
     * Size defaults to 100x100
     */
    Window(const char* titl); 

    /**
     * @brief Construct a new Window object
     * 
     * @param title - The title of the window 
     * @param inX  - The x size of the window
     * @param inY  - The y size of the window
     */
    Window(const char* title, int inX, int inY);

    /**
     * @brief Construct a new Window object
     * 
     * @param inX 
     * @param inY 
     */
    Window(int inX, int inY);

    /**
     * @brief Set the x position that the window will start at
     * 
     * @param x - the x length
     * @param y - the y length
     */
    void setStartPos(int x, int y);

    /**
     * @brief The object to add to the window.
     * 
     * @param disp - A DisplayObject member... all objects are children of DisplayObject
     */
    void addObject(DisplayObject* disp);

    /**
     * @brief A static function. Initalizes OpenGL
     * 
     * @param argc - the number arguments passed into the program
     * @param argv - the char** of the arguments passed into the program
     */
    static void initGL(int &argc, char** argv);

    /**
     * @brief The Main Display Function. Calls each object's display function in the order added.
     * 
     */
    static void mainDisplay();

    /**
     * @brief Get the Size X object
     * 
     * @return int 
     */
    int getSizeX();

    /**
     * @brief Get the Size Y object
     * 
     * @return int 
     */
    int getSizeY();

    /**
     * @brief Get the Title string
     * 
     * @return const char* 
     */
    const char* getTitle();

    /**
     * @brief Run the mainLoop of OpenGL. A blocking call
     * 
     */
    void mainLoop();

    /**
     * @brief Launch the window. 
     * (This actually opens the window... call mainLoop() "activate" the functionality of the window) 
     * 
     */
    void launch();
    
};


#endif