/**
 * @file shader.cpp
 * @author Ben Carter and Josh Canode
 * @brief This is the source file for the shader class.
 * @version 0.1
 * @date 2023-10-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "Shader.h"
#include <fstream>
#include <sstream>

Shader::Shader()
{
    fragShader = 0;
    shaderProgram = 0;
    vertexShader = 0;
}

void Shader::addShaderFromFile(const char* filename)
{
    // Build the full path to the shader file
    std::string shaderPath = "./shaders/";
    shaderPath += filename;

    std::string shaderSource;
    std::ifstream shaderFile(shaderPath.c_str());

    if (!shaderFile.is_open()) {
        std::cerr << "Failed to open shader file: " << shaderPath << std::endl;
        return;
    }

    std::stringstream shaderStream;
    shaderStream << shaderFile.rdbuf();
    shaderSource = shaderStream.str();

    // Determine shader type based on the file extension
    size_t dotIndex = std::string(filename).find_last_of(".");
    if (dotIndex != std::string::npos) {
        std::string extension = std::string(filename).substr(dotIndex + 1);
        if (extension == "vs") {
            addShaderFromCharVertex(shaderSource.c_str());
        }
        else if (extension == "frag") {
            addShaderFromCharFrag(shaderSource.c_str());
        }
        else {
            std::cerr << "Unsupported shader file extension: " << extension << std::endl;
        }
    }
    else {
        std::cerr << "Unable to determine shader type from the file extension." << std::endl;
    }
}


void Shader::addShaderFromCharVertex(const char* str)
{
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &str, NULL);
    glCompileShader(vertexShader);

    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

void Shader::addShaderFromCharFrag(const char* str)
{
    fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, &str, NULL);
    glCompileShader(fragShader);

    int  success;
    char infoLog[512];
    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

void Shader::createProgram()
{
    shaderProgram = glCreateProgram();
   
   if(vertexShader != 0)
    {
        glAttachShader(shaderProgram, vertexShader);
    }
    if(fragShader != 0)
    {
        glAttachShader(shaderProgram, fragShader);
    }
    
    glLinkProgram(shaderProgram);
    int  success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::LINK::FAILED\n" << infoLog << std::endl;
    }

    if(vertexShader != 0)
    {
        glDeleteShader(vertexShader);
    }
    if(fragShader != 0)
    {
        glDeleteShader(fragShader);
    }
}

void Shader::useShader()
{
    glUseProgram(shaderProgram);
}

void Shader::setUniform4f(UniformVar ufVar, float a, float b, float c, float d) // uniform for all shader/frag and all points.
{
    glUniform4f(ufVar.location,a,b,c,d);
}
void Shader::setUniform3f(UniformVar ufVar, float a, float b, float c) // uniform for all shader/frag and all points.
{
    glUniform3f(ufVar.location,a,b,c);
}

void Shader::setUniform1i(UniformVar ufVar, int a) // uniform for all shader/frag and all points.
{
    glUniform1i(ufVar.location,a);
}

void Shader::setUniformV3(UniformVar ufVar, glm::vec3 &a) // uniform for all shader/frag and all points.
{
    glUniform3f(ufVar.location,a.x,a.y,a.z);
}

void Shader::setUniformV4(UniformVar ufVar, glm::vec4 &a) // uniform for all shader/frag and all points.
{
    glUniform4f(ufVar.location,a.x,a.y,a.z,a.w);
}

UniformVar Shader::addUniform(const char* c)
{
    UniformVar uf = UniformVar(c);
    int loc = glGetUniformLocation(shaderProgram, uf.varname);
    uf.location = loc;
    uniformVars.push_back(uf);
    return uf;
}

void Shader::setUniformGLM(UniformVar ufVar, glm::mat4 &t)
{
    glUniformMatrix4fv(ufVar.location, 1, GL_FALSE, glm::value_ptr(t));
}