

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <cmath>

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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
    glEnable(GL_DEPTH_TEST);  

/*
    glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);

    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f); 
    glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
    glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);
*/
  //  glm::mat4 view;
  //  view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), // position
  //                      glm::vec3(0.0f, 0.0f, 0.0f), // target
  //                      glm::vec3(0.0f, 1.0f, 0.0f)); // up vector.

    // Buffers. 
    // Make a triangle (several)
   float vertices[] = {
    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,

    -0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,

    -0.5f,  0.5f,  0.5f, 
    -0.5f,  0.5f, -0.5f, 
    -0.5f, -0.5f, -0.5f, 
    -0.5f, -0.5f, -0.5f, 
    -0.5f, -0.5f,  0.5f, 
    -0.5f,  0.5f,  0.5f,

     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,

    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f, -0.5f,

    -0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,
    };

    // Make a "index" list... don't repeat above, just specify the index orders.

    Shader myShader = Shader();
    myShader.addShaderFromFile("3DPosition.vs");
    myShader.addShaderFromFile("3DPosition.frag");

    myShader.createProgram();

   // myShader.addShaderFromCharVertex(vertexShaderSource);
    //myShader.addShaderFromCharFrag(fragShaderSource);
   // myShader.createProgram();

    unsigned int VAO;
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

   // unsigned int EBO;
  //  glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    // create buffer. Holds the shader output....
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    // (location, # of data types, the data type, normalizeVector??, how far apart are the "structures" passed in (or how many bytes is one structure?), offset number of bytes)
    // location: matches the location = 0 (as can have multiple vertex attrib)
    // # of data types: there are 3 floats in a vec3
    // Do not normalize
    // Each "vector calculation in total" requires 3 * sizeof(float) to run
    // Start at the first byte (byte 0)
    glEnableVertexAttribArray(0);  

    // assign the index
   // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  //  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); 

    UniformVar myColor = UniformVar();
    myColor.varname = "mixColor";

    myShader.addUniform(&myColor);

     // transforms
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f)); 
    UniformVar modelUniform = UniformVar();
    modelUniform.varname = "model";

    // view
    // note that we're translating the scene in the reverse direction of where we want to move
    UniformVar viewUniform = UniformVar();
    viewUniform.varname = "view";

    // projection
    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    UniformVar projectionUniform = UniformVar();
    projectionUniform.varname = "projection";

    myShader.addUniform(&modelUniform);
    myShader.addUniform(&viewUniform);
    myShader.addUniform(&projectionUniform);
    model = glm::rotate(model, glm::radians(0.1f), glm::vec3(0.0f, 1.0f, 0.0f)); 
        
    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f), 
        glm::vec3( 2.0f,  5.0f, -15.0f), 
        glm::vec3(-1.5f, -2.2f, -2.5f),  
        glm::vec3(-3.8f, -2.0f, -12.3f),  
        glm::vec3( 2.4f, -0.4f, -3.5f),  
        glm::vec3(-1.7f,  3.0f, -7.5f),  
        glm::vec3( 1.3f, -2.0f, -2.5f),  
        glm::vec3( 1.5f,  2.0f, -2.5f), 
        glm::vec3( 1.5f,  0.2f, -1.5f), 
        glm::vec3(-1.3f,  1.0f, -1.5f)  
    };

    // MAIN LOOP
    float cRotate = 0.0f;
    while(!glfwWindowShouldClose(window))
    {
        
        processInput(window);

        // rendering commands
        render(window);

       
        myShader.useShader();

        glm::mat4 model2 = glm::rotate(model, (float)glfwGetTime() * glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f)); 

        myShader.setUniform4f(&myColor,1.0f,0.0f,0.0f,1.0f);
        myShader.setUniformGLM(&modelUniform, model2);
        glm::mat4 view;
        view = glm::lookAt(glm::vec3(3 * cos(cRotate), 12.0, 3 * sin(cRotate)), glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 0.0, 0.0)); 
        cRotate += 0.01;
        myShader.setUniformGLM(&viewUniform, view);
        myShader.setUniformGLM(&projectionUniform, projection);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES,0, 36);
        for(unsigned int i = 1; i < 10; i++)
        {
            glm::mat4 modelEx = glm::translate(model, cubePositions[i]);
            float angle = 10.0f * i; 
            modelEx = glm::rotate(modelEx, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            myShader.setUniformGLM(&modelUniform, modelEx);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

    //    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}