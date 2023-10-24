

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"

#include <iostream>

#ifndef CC
#define CC(arg) (arg / 255.0f)
#endif


void makeWindow(GLFWwindow* &window)
{
    window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);
}

void resizeFunc(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* &window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

void render(GLFWwindow* &window)
{
    glClearColor(CC(30),CC(50),CC(20),1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window;
    makeWindow(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }    

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, resizeFunc);  

    // Buffers. 
    // Make a triangle (several)
    float vertices[] = {
     0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f, // top right
     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, // bottom right
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom left
    -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  // top left 
};

    // Make a "index" list... don't repeat above, just specify the index orders.
    unsigned int indices[] = {
        0,1,3,  // first triangle
        1,2,3   // second triangle
    };

    Shader myShader = Shader();
    myShader.addShaderFromFile("example.vs");
    myShader.addShaderFromFile("example.frag");

    myShader.createProgram();

    

   // myShader.addShaderFromCharVertex(vertexShaderSource);
    //myShader.addShaderFromCharFrag(fragShaderSource);
   // myShader.createProgram();

    unsigned int VAO;
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    unsigned int EBO;
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    // create buffer. Holds the shader output....
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    // (location, # of data types, the data type, normalizeVector??, how far apart are the "structures" passed in (or how many bytes is one structure?), offset number of bytes)
    // location: matches the location = 0 (as can have multiple vertex attrib)
    // # of data types: there are 3 floats in a vec3
    // Do not normalize
    // Each "vector calculation in total" requires 3 * sizeof(float) to run
    // Start at the first byte (byte 0)
    glEnableVertexAttribArray(0);  

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1); 

    // assign the index
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); 

    UniformVar myColor = UniformVar();
    myColor.varname = "mixColor";

    myShader.addUniform(&myColor);

    // MAIN LOOP
    while(!glfwWindowShouldClose(window))
    {
        processInput(window);

        // rendering commands
        
        render(window);

        myShader.useShader();
        myShader.setUniform4f(&myColor,1.0f,0.0f,0.0f,1.0f);
        
        glBindVertexArray(VAO);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}