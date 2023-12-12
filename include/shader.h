// Shader Class

#pragma once

#include <string> // Include string
#include <fstream> // Include fstream
#include <sstream> // Include sstream
#include <iostream> // Include iostream

#include <GL/glew.h> // Include glew

using namespace std; // Use namespace std

class Shader {
public:
    GLuint Program; // Initialize GLuint 
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath) { // Shader constructor
        // Retrieve vertex/fragment code from path
        string vertexCode; // Initialize vertexCode string
        string fragmentCode; // Initialize fragmentCode string
        ifstream vShaderFile; // Initialize file for vertex shader
        ifstream fShaderFile; // Initialize file for fragment shader
        // Allows for exceptions
        vShaderFile.exceptions(ifstream::badbit); // Allow vs file exception
        fShaderFile.exceptions(ifstream::badbit); // Allow frag file exception
        // Read Shaders
        try {
            // Open Files
            vShaderFile.open(vertexPath); // Try opening .vs using path
            fShaderFile.open(fragmentPath); // Try opening .frag using path
            stringstream vShaderStream, fShaderStream; // Initalize stringstream for both
            // Read file's buffer contents into streams
            vShaderStream << vShaderFile.rdbuf(); // Read in .vs
            fShaderStream << fShaderFile.rdbuf(); // Read in .frag
            // Close file handlers
            vShaderFile.close(); // Close .vs file
            fShaderFile.close(); // Close .frag file
            // Convert stream into string
            vertexCode = vShaderStream.str(); // Convert and store contents of .vs as string
            fragmentCode = fShaderStream.str(); // Convert and store contents of .frag as string
        }
        catch (ifstream::failure e) {
            cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << endl; // Error message if catch
        }
        // Compilation
        const GLchar* vShaderCode = vertexCode.c_str(); // Initialize GLchar* for vs
        const GLchar* fShaderCode = fragmentCode.c_str(); // Initalize GLchar* for frag
        GLuint vertex, fragment; // Initalize GLuint for vs and frag
        GLint success; // Initalize GLint for success
        GLchar infoLog[512]; // Initialize infoLog
        // Vertex Shader
        vertex = glCreateShader(GL_VERTEX_SHADER); // Set vertex = shader
        glShaderSource(vertex, 1, &vShaderCode, NULL); // Get source
        glCompileShader(vertex); // Compile vertex shader
        // Print compile errors if necessary
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success); // Get status
        if (!success) { // If failure
            glGetShaderInfoLog(vertex, 512, NULL, infoLog); // Get info on failure
            cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl; // Print error message if catch
        }
        // Fragment Shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER); // Initalize gragment as shader
        glShaderSource(fragment, 1, &fShaderCode, NULL); // Get source
        glCompileShader(fragment); // Compile fragment shader
        // Print compile errors if necessary
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success); // Get status
        if (!success) { // If failure
            glGetShaderInfoLog(fragment, 512, NULL, infoLog); // Get info on failure
            cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl; // Print error message if catch
        }
        // Linking Shader Program
        this->Program = glCreateProgram(); // Set program to createProgram output
        glAttachShader(this->Program, vertex); // Attach vertex shader
        glAttachShader(this->Program, fragment); // Attach frag shader
        glLinkProgram(this->Program); // Link program
        // Print linking errors if necessary
        glGetProgramiv(this->Program, GL_LINK_STATUS, &success); // Get linking status
        if (!success) { // If failure
            glGetProgramInfoLog(this->Program, 512, NULL, infoLog); // Get info on failure
            cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << endl; // Print error message if catch
        }
        // Delete shaders
        glDeleteShader(vertex); // Delete vertex shader
        glDeleteShader(fragment); // Delete fragment shader
    }
    // Uses the current shader
    void Use() {
        glUseProgram(this->Program); // Use program with shaders from method above
    }
};
