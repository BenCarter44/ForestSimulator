#ifndef SHADER_CUSTOM_H
#define SHADER_CUSTOM_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct UniformVar
{
    const char* varname;
    int location;
    UniformVar(const char* c)
    {
        varname = c;
    }
};

class Shader
{
private:
    unsigned int vertexShader;
    unsigned int fragShader;
    unsigned int shaderProgram;

    std::vector<UniformVar> uniformVars;

public:
    Shader();
    void addShaderFromFile(const char* filename);
    void addShaderFromCharVertex(const char* str);
    void addShaderFromCharFrag(const char* str);
    void createProgram();
    void useShader();
    UniformVar addUniform(const char* c);

    void setUniform4f(UniformVar ufVar, float a, float b, float c, float d); // uniform for all shader/frag and all points.
    void setUniform3f(UniformVar ufVar, float a, float b, float c); // uniform for all shader/frag and all points.
    void setUniformGLM(UniformVar ufVar, glm::mat4 &t);
    void setUniformV3(UniformVar ufVar, glm::vec3 &v);
    void setUniformV4(UniformVar ufVar, glm::vec4 &v);
};




#endif