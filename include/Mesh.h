#pragma once
// Std. Includes
#include <string> // Include string
#include <fstream> // Include fstream
#include <sstream> // Include sstream
#include <iostream> // Include iostream
#include <vector> // Include vector
using namespace std; // Use namespace std
// GL Includes
#include <GL/glew.h> // Contains all the necessery OpenGL includes
#include <glm/glm.hpp> // Include glm
#include <glm/gtc/matrix_transform.hpp> // Include matrix transform


// Define vertex structure
struct Vertex {
    // Position
    glm::vec3 Position; // Vec3 position
    // Normal
    glm::vec3 Normal; // Vec3 normal
    // TexCoords
    glm::vec2 TexCoords; // Vec2 texture coordinates
};

// Define texture structure
struct Texture {
    GLuint id; // GLuint for id
    string type; // String for type
    aiString path; // aiString for path
};

class Mesh {  // Provided in class
public:
    /*  Mesh Data  */
    vector<Vertex> vertices; // vector of vertices
    vector<GLuint> indices; // vector of indices
    vector<Texture> textures; // vector of textures

    /*  Functions  */
    // Constructor
    Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures) // Input constructor
    {
        this->vertices = vertices; // Set vertices equal to input
        this->indices = indices; // Set indices equal to input
        this->textures = textures; // Set textures equal to input

        // Now that we have all the required data, set the vertex buffers and its attribute pointers.
        this->setupMesh(); // Call class setupMesh() method
    }

    // Render the mesh
    void Draw(Shader shader) 
    {
        // Bind appropriate textures
        GLuint diffuseNr = 1; // Set diffuseNr
        GLuint specularNr = 1; // Set specularNr
        for(GLuint i = 0; i < this->textures.size(); i++) // Iterate over textures
        {
            glActiveTexture(GL_TEXTURE0 + i); // Active proper texture unit before binding
            // Retrieve texture number (the N in diffuse_textureN)
            stringstream ss; // initialize stringstream
            string number; // Initalize number
            string name = this->textures[i].type; // Set name to type
            if(name == "texture_diffuse") // If diffuse
                ss << diffuseNr++; // Transfer GLuint to stream
            else if(name == "texture_specular") // If specular
                ss << specularNr++; // Transfer GLuint to stream
            number = ss.str(); // Set number equal to string of ss
            // Now set the sampler to the correct texture unit
            glUniform1i(glGetUniformLocation(shader.Program, (name + number).c_str()), i); // Set sampler to texture unit
            // And finally bind the texture
            glBindTexture(GL_TEXTURE_2D, this->textures[i].id); // Bind
        }
        
        // Also set each mesh's shininess property to a default value (if you want you could extend this to another mesh property and possibly change this value)
        glUniform1f(glGetUniformLocation(shader.Program, "material.shininess"), 16.0f);

        // Draw mesh
        glBindVertexArray(this->VAO); // Bind VAO
        glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0); // Draw GL_TRIANGLES
        glBindVertexArray(0); // Bind 0

        // Always good practice to set everything back to defaults once configured.
        for (GLuint i = 0; i < this->textures.size(); i++)
        {
            glActiveTexture(GL_TEXTURE0 + i); // Reset active texture
            glBindTexture(GL_TEXTURE_2D, 0); // Bind GL_TEXTURE_2D, 0
        }
    }

private:
    /*  Render data  */
    GLuint VAO, VBO, EBO; // Initialize VAO, VBO, EBO

    /*  Functions    */
    // Initializes all the buffer objects/arrays
    void setupMesh()
    {
        // Create buffers/arrays
        glGenVertexArrays(1, &this->VAO); // Create VAO array
        glGenBuffers(1, &this->VBO); // Create VBO buffer
        glGenBuffers(1, &this->EBO); // Create EBO buffer

        glBindVertexArray(this->VAO); // Bind vertex array
        // Load data into vertex buffers
        glBindBuffer(GL_ARRAY_BUFFER, this->VBO); // Bind buffer
        // A great thing about structs is that their memory layout is sequential for all its items.
        // The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
        // again translates to 3/2 floats which translates to a byte array.
        glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), &this->vertices[0], GL_STATIC_DRAW);   // Set buffer data

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO); // Bind EBO buffer
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), &this->indices[0], GL_STATIC_DRAW); // Set buffer data

        // Set the vertex attribute pointers
        // Vertex Positions
        glEnableVertexAttribArray(0); // Enable vertex attrib
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0); // Set vertex attrib for position
        // Vertex Normals
        glEnableVertexAttribArray(1); // Enable vertex attrib
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normal)); // Set vertex attrib for normal
        // Vertex Texture Coords
        glEnableVertexAttribArray(2); // Enable vertex attrib
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, TexCoords)); // Set vertex attrib for texcoords

        glBindVertexArray(0); // Bind 0
    }
};

