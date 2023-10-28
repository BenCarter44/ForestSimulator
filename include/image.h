#ifndef IMAGE_H
#define IMAGE_H

#include <glad/glad.h>
#include <string>
#include <iostream>
#include "Shader.h"

class Image {
public:
    Image(const std::string& imagePath);
    ~Image();

    // Set the texture unit for this image
    void setTextureUnit(int unit);

    // Bind the texture to the specified texture unit and set the uniform in the shader
    void bindAndSetUniform(Shader& shader);

    GLuint getTextureID();

private:
    GLuint textureID;
    int textureUnit;  // New member variable to store the texture unit

    GLuint loadTexture(const std::string& imagePath);
};


#endif
