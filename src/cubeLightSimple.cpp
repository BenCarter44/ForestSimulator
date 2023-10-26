

#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#ifndef CC
#define CC(arg) (arg / 255.0f)
#endif

#ifndef IGNOREIGNORE

void makeWindow(GLFWwindow* &window)
{
    window = glfwCreateWindow(800, 600, "Light Diffuse", NULL, NULL);
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
    glClearColor(CC(20),CC(20),CC(20),1.0f);
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

    // Buffers. 
    // Make a triangle (several)
    float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};

    Shader lightingShader;
    lightingShader.addShaderFromFile("3DColor.vs");
    lightingShader.addShaderFromFile("3DColor.frag");
    lightingShader.createProgram();

    Shader lightCubeShader;
    lightCubeShader.addShaderFromFile("3DLightSource.vs");
    lightCubeShader.addShaderFromFile("3DLightSource.frag");
    lightCubeShader.createProgram();

   // myShader.addShaderFromCharVertex(vertexShaderSource);
    //myShader.addShaderFromCharFrag(fragShaderSource);
   // myShader.createProgram();

    unsigned int cubeVAO;
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &cubeVAO);

    glBindVertexArray(cubeVAO);
    // create buffer. Holds the shader output....
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0); 
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);  
    // (location, # of data types, the data type, normalizeVector??, how far apart are the "structures" passed in (or how many bytes is one structure?), offset number of bytes)
    // location: matches the location = 0 (as can have multiple vertex attrib)
    // # of data types: there are 3 floats in a vec3
    // Do not normalize
    // Each "vector calculation in total" requires 3 * sizeof(float) to run
    // Start at the first byte (byte 0)
    
    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    unsigned int lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // note that we update the lamp's position attribute's stride to reflect the updated buffer data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    UniformVar modelLS = lightCubeShader.addUniform("model");
    UniformVar viewLS = lightCubeShader.addUniform("view");
    UniformVar projectionLS = lightCubeShader.addUniform("projection");
    UniformVar lightColorLS = lightCubeShader.addUniform("lightColor");

    UniformVar modelU = lightingShader.addUniform("model");
    UniformVar viewU = lightingShader.addUniform("view");
    UniformVar projectionU = lightingShader.addUniform("projection");

    UniformVar lightPosU = lightingShader.addUniform("lightPos");
    UniformVar lightColorU = lightingShader.addUniform("lightColor");
    UniformVar objectColorU = lightingShader.addUniform("objectColor");

    // view
    // note that we're translating the scene in the reverse direction of where we want to move
    glm::mat4 view = glm::lookAt(glm::vec3(3.0f, 2.0f, 3.0f), // position
                        glm::vec3(0.0f, 0.0f, 0.0f), // target
                        glm::vec3(0.0f, 1.0f, 0.0f)); // up vector.

    // projection
    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    lightingShader.useShader();
    lightingShader.setUniformGLM(viewU, view);
    lightingShader.setUniformGLM(projectionU, projection);

    lightCubeShader.useShader();
    lightCubeShader.setUniformGLM(viewLS, view);
    lightCubeShader.setUniformGLM(projectionLS, projection);

    // MAIN LOOP
    while(!glfwWindowShouldClose(window))
    {
        processInput(window);

        // rendering commands
        render(window);

        glm::vec3 lightPos(-1.0f, 1.0f, -1.0f);

        // transforms
        glm::mat4 model = glm::mat4(1.0f);
        glm::vec3 boxPosition = glm::vec3(0,0,0);
        model = glm::translate(model, boxPosition);


        // transforms
        lightingShader.useShader();
        lightingShader.setUniformGLM(modelU, model);


        glm::vec3 lightColor(1.0f, 0.9f, 0.3f);
        glm::vec3 toyColor(1.0f, 0.5f, 0.31f);
        glm::vec3 result = lightColor * toyColor; // = (1.0f, 0.5f, 0.31f);  Color equals the light x the toyColor. ToyColor: What reflected.

        lightingShader.setUniformV3(objectColorU, toyColor);
        lightingShader.setUniformV3(lightColorU, lightColor);        

        lightingShader.setUniformV3(lightPosU, lightPos);

        glBindVertexArray(cubeVAO);
        glDrawArrays(GL_TRIANGLES,0, 36);

        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f)); 
        
        lightCubeShader.useShader();
        lightCubeShader.setUniformGLM(modelLS, model);
        lightCubeShader.setUniformV3(lightColorLS, lightColor);


        glBindVertexArray(lightCubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}

#endif