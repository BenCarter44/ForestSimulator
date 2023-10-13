#include "TextureHandler.h"

Texture::Texture()
{

}
Texture::Texture(const char* filename)
{
    this->filename = std::string("textures/") + std::string(filename);
    
    textureID = 0;
    size = 1;
    
}

Texture::Texture(const char* filename, int size)
{
    this->filename = std::string("textures/") + std::string(filename);
    
    textureID = 0;
    this->size = size;
}

int Texture::setupTexture()
{
    printf("Loading Texture: %s\n",filename.c_str());
    textureID = SOIL_load_OGL_texture(
        filename.c_str(),  // Replace with the path to your .jpg file
        SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y
    );

    if (!textureID) 
    {
        printf("Error loading Texture: %s\n", SOIL_last_result());
        return -1;
    }
    return 0;
}

void Texture::start()
{
    glEnable(GL_TEXTURE_2D);
    // Bind the Texture
    glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::stop()
{
    glDisable(GL_TEXTURE_2D);
}

void Texture::markCoord(float x, float y)
{
    std::cout << "glTexCoord2f(" << x / (float)size << ", " << y / (float)size << "); " << std::endl;
    glTexCoord2f(x / (float)size, y / (float)size);
}