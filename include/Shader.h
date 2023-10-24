#ifndef SHADER_CUSTOM_H
#define SHADER_CUSTOM_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>

struct UniformVar
{
    const char* varname;
    int location;
};

class Shader
{
private:
    unsigned int vertexShader;
    unsigned int fragShader;
    unsigned int shaderProgram;

    std::vector<UniformVar*> uniformVars;

public:
    Shader();
    void addShaderFromFile(const char* filename);
    void addShaderFromCharVertex(const char* str);
    void addShaderFromCharFrag(const char* str);
    void createProgram();
    void useShader();
    void addUniform(UniformVar* ufVar);

    void setUniform4f(UniformVar* ufVar, float a, float b, float c, float d); // uniform for all shader/frag and all points.
    void setUniform3f(UniformVar* ufVar, float a, float b, float c); // uniform for all shader/frag and all points.


};


#endif