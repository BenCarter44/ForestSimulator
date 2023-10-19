#ifndef SHADER_CUSTOM_H
#define SHADER_CUSTOM_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>

class Shader
{
private:
    unsigned int vertexShader;
    unsigned int fragShader;
    unsigned int shaderProgram;

public:
    Shader();
    void addShaderFromFile(const char* filename);
    void addShaderFromCharVertex(const char* str);
    void addShaderFromCharFrag(const char* str);
    void createProgram();
    void useShader();
};


#endif