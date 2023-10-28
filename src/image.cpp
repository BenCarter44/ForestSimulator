#include "image.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Image::Image(const std::string& imagePath) {
    textureID = loadTexture(imagePath);
    // Initialize the texture unit to 0 by default
    textureUnit = 0;
}

Image::~Image() {
    glDeleteTextures(1, &textureID);
}

void Image::setTextureUnit(int unit) {
    textureUnit = unit;
}

void Image::bindAndSetUniform(Shader& shader) {
    // Activate the texture unit and bind the texture
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(GL_TEXTURE_2D, textureID);
    // Set the uniform in the shader
    shader.setUniformInt("textureSampler", textureUnit);
}

void Image::bind() {
    glBindTexture(GL_TEXTURE_2D, textureID);
}

GLuint Image::getTextureID() {
    return textureID;
}

GLuint Image::loadTexture(const std::string& imagePath) {
    GLuint textureID;
    glGenTextures(1, &textureID);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // Flip the image vertically
    unsigned char* data = stbi_load(imagePath.c_str(), &width, &height, &nrChannels, 0);
    
    if (data) {
        GLenum format;
        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 3)
            format = GL_RGB;
        else if nrChannels == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        // Set texture parameters (optional)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    } else {
        std::cout << "Failed to load texture: " << imagePath << std::endl;
        stbi_image_free(data); // Free resources
    }

    return textureID;
}
