

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stb_image.h>

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
    glClearColor(CC(52),CC(52),CC(52),1.0f);
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

    float texCoords[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,   0.75,
         0.5f,  0.5f, -0.5f,  1.0f,   0.75,
        -0.5f,  0.5f, -0.5f,  0.0f,   0.75,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,   0.75,
         0.5f,  0.5f,  0.5f,  1.0f,   0.75,
        -0.5f,  0.5f,  0.5f,  0.0f,   0.75,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f,   0.75,
        -0.5f, -0.5f, -0.5f,  0.0f,   0.75,
        -0.5f, -0.5f, -0.5f,  0.0f,   0.75,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,   0.75,
         0.5f, -0.5f, -0.5f,  0.0f,   0.75,
         0.5f, -0.5f, -0.5f,  0.0f,   0.75,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f,   0.75,
         0.5f, -0.5f, -0.5f,  1.0f,   0.75,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,   0.75,

        -0.5f,  0.5f, -0.5f,  0.0f,   0.75,
         0.5f,  0.5f, -0.5f,  1.0f,   0.75,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,   0.75

 
};
    
    float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load and generate the texture
    int width, height, nrChannels;
    unsigned char *data = stbi_load("textures/Background.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);



    Shader lightingShader;
    lightingShader.addShaderFromFile("3DColor.vs");
    lightingShader.addShaderFromFile("3DColor.frag");
    lightingShader.createProgram();

    Shader lightCubeShader;
    lightCubeShader.addShaderFromFile("3DLightSource.vs");
    lightCubeShader.addShaderFromFile("3DLightSource.frag");
    lightCubeShader.createProgram();

    Shader textShader;
    textShader.addShaderFromFile("textObject.vs");
    textShader.addShaderFromFile("textObject.frag");
    textShader.createProgram();
    UniformVar textVar = textShader.addUniform("ourTexture");
    textShader.setUniform1i(textVar, 0);

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

    //text shader
     unsigned int textVBO, textVAO;
    glGenVertexArrays(1, &textVAO);
    glGenBuffers(1, &textVBO);

    glBindVertexArray(textVAO);

    glBindBuffer(GL_ARRAY_BUFFER, textVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

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
    UniformVar lightSettingsU = lightingShader.addUniform("lightSettings");
    UniformVar camPosU = lightingShader.addUniform("camPos");

    //text
    UniformVar modelTXT = textShader.addUniform("model");
    UniformVar viewTXT = textShader.addUniform("view");
    UniformVar projectionTXT = textShader.addUniform("projection");

    // view
    glm::vec3 camPos = glm::vec3(0.0f, 0.0f, 9.0f);
    // note that we're translating the scene in the reverse direction of where we want to move
    glm::mat4 view = glm::lookAt(camPos, // position
                        glm::vec3(0.0f, 0.0f, 0.0f), // target
                        glm::vec3(0.0f, 1.0f, 0.0f)); // up vector.

    // projection
    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    lightingShader.useShader();
    lightingShader.setUniformGLM(viewU, view);
    lightingShader.setUniformGLM(projectionU, projection);
    lightingShader.setUniformV3(camPosU, camPos);

    lightCubeShader.useShader();
    lightCubeShader.setUniformGLM(viewLS, view);
    lightCubeShader.setUniformGLM(projectionLS, projection);

    textShader.useShader();
    textShader.setUniformGLM(viewTXT, view);
    textShader.setUniformGLM(projectionTXT, projection);


    // MAIN LOOP
    while(!glfwWindowShouldClose(window))
    {
        


        processInput(window);

        // rendering commands
        render(window);

        glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
        glm::vec3 toyColor(1.0f, 0.5f, 0.31f);

        glm::vec3 lightPosOriginal(-4.0f, 2.1f, 3.5f);
        glm::vec4 lightSettings(0.3f, 0.4f, 0.4f, 0.0f);
        
        for(int cubeI = 0; cubeI < 4; cubeI++)
        {
            glm::vec3 newLightTranslate = glm::vec3(cubeI * 2.6,0,0);
            glm::vec3 lightPos = lightPosOriginal + newLightTranslate;
            glm::vec4 specularStrength = glm::vec4(0.0f, 0.0f, 0.0f, pow(2, 1 + cubeI));
            glm::vec4 renderedLightSettings = lightSettings + specularStrength;

            // transforms
            glm::mat4 model = glm::mat4(1.0f);
            glm::vec3 boxPosition = glm::vec3(-3 + cubeI * 2,1.5,0);
            model = glm::translate(model, boxPosition);
            //glm::vec3 scale
            glm::vec3 scalar = glm::vec3(1.2, 1.2, 1.2);
            model = glm::scale(model, scalar);
            model = glm::rotate(model, glm::radians(30.0f - cubeI * 5.0f), glm::vec3(0.0,1.0,0.0));


            // transforms
            lightingShader.useShader();
            lightingShader.setUniformGLM(modelU, model);

            lightingShader.setUniformV3(objectColorU, toyColor);
            lightingShader.setUniformV3(lightColorU, lightColor);  
            lightingShader.setUniformV4(lightSettingsU, renderedLightSettings);      

            lightingShader.setUniformV3(lightPosU, lightPos);

            glBindVertexArray(cubeVAO);
            glDrawArrays(GL_TRIANGLES,0, 36);

            model = glm::mat4(1.0f);
            model = glm::translate(model, lightPos);
            model = glm::scale(model, glm::vec3(0.2f)); 
            
            lightCubeShader.useShader();
            lightCubeShader.setUniformGLM(modelLS, model);
            lightCubeShader.setUniformV3(lightColorLS, lightColor);


           // glBindVertexArray(lightCubeVAO);
           // glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        for(int cubeI = 0; cubeI < 4; cubeI++)
        {
            glm::vec3 newLightTranslate = glm::vec3(cubeI * 2.6,-4,0);
            glm::vec3 lightPos = lightPosOriginal + newLightTranslate;
            glm::vec4 specularStrength = glm::vec4(0.0f, 0.0f, 0.0f, pow(2,cubeI + 5));
            glm::vec4 renderedLightSettings = lightSettings + specularStrength;

            // transforms
            glm::mat4 model = glm::mat4(1.0f);
            glm::vec3 boxPosition = glm::vec3(-3 + cubeI * 2,-1.5,0);
            model = glm::translate(model, boxPosition);
            //glm::vec3 scale
            glm::vec3 scalar = glm::vec3(1.2, 1.2, 1.2);
            model = glm::scale(model, scalar);
            model = glm::rotate(model, glm::radians(30.0f - cubeI * 5.0f), glm::vec3(0.0,1.0,0.0));


            // transforms
            lightingShader.useShader();
            lightingShader.setUniformGLM(modelU, model);

            lightingShader.setUniformV3(objectColorU, toyColor);
            lightingShader.setUniformV3(lightColorU, lightColor);  
            lightingShader.setUniformV4(lightSettingsU, renderedLightSettings);      

            lightingShader.setUniformV3(lightPosU, lightPos);

            glBindVertexArray(cubeVAO);
            glDrawArrays(GL_TRIANGLES,0, 36);

            model = glm::mat4(1.0f);
            model = glm::translate(model, lightPos);
            model = glm::scale(model, glm::vec3(0.2f)); 
            
            lightCubeShader.useShader();
            lightCubeShader.setUniformGLM(modelLS, model);
            lightCubeShader.setUniformV3(lightColorLS, lightColor);


            //glBindVertexArray(lightCubeVAO);
            //glDrawArrays(GL_TRIANGLES, 0, 36);
        }


        glm::mat4 model = glm::mat4(1.0f);
        glm::vec3 textPosition = glm::vec3(0,0,-5);

        model = glm::translate(model, textPosition);

        model = glm::scale(model, glm::vec3(18.0f, 15.0f, 1)); 
        model = glm::scale(model, glm::vec3(0.875,0.85,1)); 



        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);

        textShader.useShader();
        textShader.setUniformGLM(modelTXT, model);
        glBindVertexArray(textVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwPollEvents();
        glfwSwapBuffers(window);

// light.... 
        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPosOriginal);
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