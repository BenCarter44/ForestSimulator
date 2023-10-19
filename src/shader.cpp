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