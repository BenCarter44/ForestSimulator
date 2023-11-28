#include <iostream>  // iostream include

// GLEW
#define GLEW_STATIC // Define glew_static
#include <GL/glew.h> // glew include

// GLFW
#include <GLFW/glfw3.h> // glfw include

// SOIL
#include <SOIL/SOIL.h> // soil include

// GLM Mathematics
#include <glm/glm.hpp> // glm include
#include <glm/gtc/matrix_transform.hpp> // glm matrix math include
#include <glm/gtc/type_ptr.hpp> // glm gtc include

// Other includes
#include "shader.h" // Include shader class
#include "Camera.h" // Include Camera class
#include "Model.h" // Include Model class

const GLuint WIDTH = 800, HEIGHT = 600; // Global variables for width and height of window

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode); // key_callback method
void do_movement(); // Movement method

Camera camera(glm::vec3(0.0f, 0.0f, 0.0f)); // Sets iniital camera pos (0, 0, 0)
GLfloat lastX = WIDTH / 2.0; // Used for camera motion
GLfloat lastY = HEIGHT / 2.0; // Used for camera motion
bool keys[1024]; // Allowable number of key strokes

glm::vec3 lightPos(1.0f, 1.0f, -2.0f); // Sets light position

GLfloat deltaTime = 0.0f; // Initialize deltaTime for camera movement
GLfloat lastFrame = 0.0f; // Initialize lastFrame for camera movement

int main() {
    // Init GLFW
    glfwInit(); // Initialize GLFW
    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // Set major context version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // Set minor context version
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Set profiles
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); // Set resizable to false

    // Create GLFWwindow
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Project 9", nullptr, nullptr); // Create window
    glfwMakeContextCurrent(window); // Make context method

    // Set required callback functions
    glfwSetKeyCallback(window, key_callback); // Set key_callback method

    glewExperimental = GL_TRUE; // Set glew to experimental

    glewInit(); // Initialize GLEW

    glViewport(0, 0, WIDTH, HEIGHT); // Define viewport dimensions

    glEnable(GL_DEPTH_TEST); // Set up OpenGL options

    // INSERT SHADERS HERE FOR PROJECT 10
    Shader checkerboardShader("checkerboard.vs", "checkerboard.frag"); // Create shader for checkerboard
    Shader cubeShader("cube.vs", "cube.frag"); // Create shader for cube object
    Shader cylinderShader("cylinder.vs", "cylinder.frag"); // Create shader for cylinder object
    Shader sphereShader("sphere.vs", "sphere.frag"); // Create shader for sphere object

    // Models for Cylinder and Sphere
    Model cylinderModel("cylinder.obj"); // Defines model for cylinder using obj
    Model sphereModel("sphere.obj"); // Define model for sphere using obj

    GLfloat vertices[] = {
        // Coordinates: 3 Position, 3 Color, 2 Texture
        // Back face of cube
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  0.0f, -1.0f, // Bottom left
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,  0.0f, -1.0f, // Bottom right
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f,  0.0f, -1.0f, // Upper right
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f,  0.0f, -1.0f, // Upper right
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,  0.0f, -1.0f, // Upper left
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  0.0f, -1.0f, // Bottom left

        // Front face of cube
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  0.0f,  1.0f, // Bottom left
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  0.0f,  1.0f, // Bottom right
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f,  1.0f, // Upper right
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f,  1.0f, // Upper right
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f,  1.0f, // Upper left
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  0.0f,  1.0f, // Bottom left

        // Left face
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.0f,  0.0f,  0.0f, // Upper close
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, -1.0f,  0.0f,  0.0f, // Upper far
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1.0f,  0.0f,  0.0f, // Lower far
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1.0f,  0.0f,  0.0f, // Lower far
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, -1.0f,  0.0f,  0.0f, // Lower close
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.0f,  0.0f,  0.0f, // Upper close

        // Right face
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,  0.0f,  0.0f, // Upper close
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f,  0.0f, // Upper far
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  0.0f,  0.0f, // Lower far
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  0.0f,  0.0f, // Lower far
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f,  0.0f, // Lower close
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,  0.0f,  0.0f, // Upper close

        // Bottom face
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  0.0f, -1.0f,  0.0f, // Left far
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,  0.0f, -1.0f,  0.0f, // Right far
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f, -1.0f,  0.0f, // Right close
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f, -1.0f,  0.0f, // Right close
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f, -1.0f,  0.0f, // Left close
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  0.0f, -1.0f,  0.0f, // Left far

        // Top Face
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f,  0.0f, // Left far
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  1.0f,  0.0f, // Right far
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f,  0.0f, // Right close
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f,  0.0f, // Right close
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  1.0f,  0.0f, // Left close
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f,  0.0f // Left far
    };
    GLuint VBO, VAO; // Initialize VBO, VAO
    glGenVertexArrays(1, &VAO); // Generate VAO
    glGenBuffers(1, &VBO); // Generate VBO

    glBindVertexArray(VAO);  // Bind VAO

    glBindBuffer(GL_ARRAY_BUFFER, VBO);  // Bind VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);  // Buffer Data

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0); // Set vertex attribute pointer for pos
    glEnableVertexAttribArray(0); // Enable vertex attrib array with 0
    // TexCoord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat))); // Set vertex attrib pointer for texcoord
    glEnableVertexAttribArray(2); // Enable with 2
    // Normalized Position Attribute
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0); // Set normalized pos vertex attrib
    glEnableVertexAttribArray(4); // Enable with 4

    glBindVertexArray(0); // Unbind VAO

    // DEFINE TEXTURES HERE Project 10 --> NOTE FOR PROJECT 10

    // Game Loop
    while (!glfwWindowShouldClose(window)) {
        // Calculate deltaTime for camera movement
        GLfloat currentFrame = glfwGetTime(); // Get current time
        deltaTime = currentFrame - lastFrame; // Calculate change in time
        lastFrame = currentFrame; // Set last frame to current frame

        // Check for events
        glfwPollEvents(); // Callback glfwPollEvents to check for events
        do_movement(); // Callback do_movement()

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // Set background color
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear buffers

        
        // Initialize Camera
        glm::mat4 view = glm::mat4(1.0f); // Initialize view to identity
        view = camera.GetViewMatrix(); // Set view based on camera
        glm::mat4 projection = glm::perspective(45.0f, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f); // Initialize projection using initial values
        glm::mat4 model = glm::mat4(1.0f); // Initialize model to be 4x4 identity

        // BIND TEXTURES HERE PROJECT 10

        // CHECKERBOARD
        checkerboardShader.Use(); // Use checkerboard shader

        GLint squareColorLoc = glGetUniformLocation(checkerboardShader.Program, "squareColor"); // Retrieve uniform location for squareColor
        GLint lightColorLoc = glGetUniformLocation(checkerboardShader.Program, "lightColor"); // Retrieve uniform location for lightColor
        GLint lightPosLoc = glGetUniformLocation(checkerboardShader.Program, "lightPos"); // Retrieve uniform location for lightPos
        GLint viewPosLoc = glGetUniformLocation(checkerboardShader.Program, "viewPos"); // Retrieve uniform location for viewPos

        glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f); // Pass white color to lightColorLoc uniform
        glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z); // Pass light position to lightPosLoc uniform
        glUniform3f(viewPosLoc, camera.Position.x, camera.Position.y, camera.Position.z); // Pass camera position to viewPosLoc uniform

        glm::mat4 view_square = view; // Create mat4 view_square equal to view generic defined above

        GLint modelLoc = glGetUniformLocation(checkerboardShader.Program, "model"); // Retrieve model uniform location
        GLint viewLoc = glGetUniformLocation(checkerboardShader.Program, "view"); // Retrieve view uniform location
        GLint projLoc = glGetUniformLocation(checkerboardShader.Program, "projection"); // Retrieve projection uniform location

        for (int i = 0; i < 8; i++) { // For 8 rows
            for (int j = 0; j < 8; j++) { // For 8 columns
                if ((i+j) % 2 == 0) { // Check if i+j is odd or even for color purposes
                    glUniform3f(squareColorLoc, 1.0f, 0.0f, 1.0f); // If even square color is purple --> pass purple to uniform
                } else {
                    glUniform3f(squareColorLoc, 1.0f, 1.0f, 1.0f); // If even square color is white --> pas white to uniform
                }
                view_square = glm::translate(view_square, glm::vec3(j-4.0f, -0.5f, i-9.0f)); // Translate square to posiiton [setting x and z for grid]
                view_square = glm::scale(view_square, glm::vec3(1.0f, 0.1f, 1.0f)); // Scale squares to be like tiles
                glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)); // Pass model to uniform
                glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view_square)); // Pass view_square to uniform
                glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection)); // Pass projection to uniform
                // Draw square
                glBindVertexArray(VAO); // Bind vertex arrays
                glDrawArrays(GL_TRIANGLES, 0, 36); // Draw arrays for cube
                view_square = view; // Reset view_square to original view identity [i.e. Translations are independent]
                
            }
        }

        // CUBE
        cubeShader.Use(); // Activate cube shader

        // Set uniform locations
        GLint cubeColorLoc = glGetUniformLocation(cubeShader.Program, "cubeColor"); // Retrieve uniform location
        lightColorLoc = glGetUniformLocation(cubeShader.Program, "lightColor"); // Reset uniform location for cubeShader
        lightPosLoc = glGetUniformLocation(cubeShader.Program, "lightPos"); // Reset uniform location for cubeShader
        viewPosLoc = glGetUniformLocation(cubeShader.Program, "viewPos"); // Reset uniform location for cubeShader

        // Pass to shaders
        glUniform3f(cubeColorLoc, 1.0f, 0.0f, 0.0f); // Pass cube color to uniform
        glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f); // Pass light color to uniform
        glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z); // Pass light position to uniform
        glUniform3f(viewPosLoc, camera.Position.x, camera.Position.y, camera.Position.z); // Pass camera position to uniform

        glm::mat4 view_cube = view; // Create mat4 view_cube equal to identity view
        view_cube = glm::translate(view_cube, glm::vec3(0.0f, 0.0f, -5.0f)); // Translate cube back

        // Get uniform location
        modelLoc = glGetUniformLocation(cubeShader.Program, "model"); // Reset modelLoc using cubeShader
        viewLoc = glGetUniformLocation(cubeShader.Program, "view"); // Reset viewLoc using cubeShader
        projLoc = glGetUniformLocation(cubeShader.Program, "projection"); // Reset projLoc using cubeShader
        // Pass locations to shader
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)); // Pass model to shader
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view_cube)); // Pass view_cube to shader
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection)); // Pass projection to shader
        // Draw cube
        glBindVertexArray(VAO); // Bind vertex arrays
        glDrawArrays(GL_TRIANGLES, 0, 36); // Draw cube

        
        // CYLINDER
        cylinderShader.Use(); // Activate cylinder shader

        GLint cylinderColorLoc = glGetUniformLocation(cylinderShader.Program, "cylinderColor"); // Retrieve cylinderColor location
        lightColorLoc = glGetUniformLocation(cylinderShader.Program, "lightColor"); // Reset lightColor location
        lightPosLoc = glGetUniformLocation(cylinderShader.Program, "lightPos"); // Reset lightPos location
        viewPosLoc = glGetUniformLocation(cylinderShader.Program, "viewPos"); // Reset viewPos location

        glUniform3f(cylinderColorLoc, 0.0f, 1.0f, 0.0f); // Pass color to uniform
        glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f); // Pass light color to uniform
        glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z); // Pass light position to uniform
        glUniform3f(viewPosLoc, camera.Position.x, camera.Position.y, camera.Position.z); // Pass camera position to uniform

        modelLoc = glGetUniformLocation(cylinderShader.Program, "model"); // Reset view location for cylinderShader
        viewLoc = glGetUniformLocation(cylinderShader.Program, "view"); // Reset view location for cylinderShader
        projLoc = glGetUniformLocation(cylinderShader.Program, "projection"); // Reset view location for cylinderShader

        glm::mat4 view_cylinder = view; // Create mat4 view_cylinder using generic view identity
        view_cylinder = glm::translate(view_cylinder, glm::vec3(1.2f, -3.0f, -5.5f)); // Translate cylinder back, to the right, and down
        view_cylinder = glm::scale(view_cylinder, glm::vec3(0.5, 3.0, 0.5)); // Increase height of cylinder

        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view_cylinder)); // Pass view_cylinder to shader
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection)); // Pass projection to shader
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)); // Pass moel to shader

        cylinderModel.Draw(cylinderShader); // Draw obj model

        
        // SPHERE
        sphereShader.Use(); // Activate sphereShader

        GLint sphereColorLoc = glGetUniformLocation(sphereShader.Program, "sphereColor"); // Retrieve sphereColor location
        lightColorLoc = glGetUniformLocation(sphereShader.Program, "lightColor"); // Reset lightColor location for sphereShader
        lightPosLoc = glGetUniformLocation(sphereShader.Program, "lightPos"); // Reset lightPos location for sphereShader
        viewPosLoc = glGetUniformLocation(sphereShader.Program, "viewPos"); // Reset viewPos location for sphereShader

        glUniform3f(sphereColorLoc, 0.0f, 0.0f, 1.0f); // Pass in sphere color to uniform
        glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f); // Pass in light color to uniform
        glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z); // Pass in light position to uniform
        glUniform3f(viewPosLoc, camera.Position.x, camera.Position.y, camera.Position.z); // Pass in camera position to uniform

        modelLoc = glGetUniformLocation(sphereShader.Program, "model"); // Reset model uniform location for sphereShader
        viewLoc = glGetUniformLocation(sphereShader.Program, "view"); // Reset view uniform location for sphereShader
        projLoc = glGetUniformLocation(sphereShader.Program, "projection"); // Reset projection uniform location for sphereShader

        glm::mat4 view_sphere = view; // Create mat4 view_sphere equal to view identity
        view_sphere = glm::translate(view_sphere, glm::vec3(-1.2f, 0.0f, -5.0f)); // Translate sphere back and to the left
        view_sphere = glm::scale(view_sphere, glm::vec3(0.5f, 0.5f, 0.5f)); // Scale down sphere
        
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view_sphere)); // Pass view_sphere to uniform
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection)); // Pass projection to uniform
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)); // Pass model to uniform

        sphereModel.Draw(sphereShader); // Draw sphere obj model

        glBindVertexArray(0); // Bind zero at end
        glfwSwapBuffers(window); // Swap screen buffers

    }
    // Deallocate resources
    glDeleteVertexArrays(1, &VAO); // Deallocate vertex arrays
    glDeleteBuffers(1, &VBO); // Deallocate buffers
    glfwTerminate(); // Terminate window
    return 0; // Returns 0 for end of int main()

}

// Method for key input
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) { // If ESC pressed
        glfwSetWindowShouldClose(window, GL_TRUE); // Close window
    } if (key >= 0 && key < 1024) { // Allow for 1024 key presses
        if (action == GLFW_PRESS) { // If pressed
            keys[key] = true; // Set keys[key] = true [key pressed]
        } else if (action == GLFW_RELEASE) { // If released
            keys[key] = false; // Set keys[key] = false [key not pressed]
        }
    }
}

// Initiates movement based on keyboard input
void do_movement() {
    if (keys[GLFW_KEY_LEFT_SHIFT] || keys[GLFW_KEY_RIGHT_SHIFT]) { // If either shift keys are pressed
        if (keys[GLFW_KEY_UP]) { // If up arrow
            camera.ProcessKeyboard(FORWARD, deltaTime); // Move camera forward with callback
        } else if (keys[GLFW_KEY_DOWN]) { // If down arrow
            camera.ProcessKeyboard(BACKWARD, deltaTime); // Move camera backward with callback
        } else if (keys[GLFW_KEY_COMMA]) { // If comma --> less than symbol
            camera.ProcessKeyboard(UPROLL, deltaTime); // Move camera in positive roll with callback
        } else if (keys[GLFW_KEY_PERIOD]) { // If period --> greater than symbol
            camera.ProcessKeyboard(DOWNROLL, deltaTime); // Move camera in negative roll with callback
        }
    }
    else if (keys[GLFW_KEY_LEFT_CONTROL] || keys[GLFW_KEY_RIGHT_CONTROL]) { // If either ctrl key is pressed
        if (keys[GLFW_KEY_DOWN]) { // If down arrow
            camera.ProcessKeyboard(UPPITCH, deltaTime); // Move camera in positive pitch with callback
        } else if (keys[GLFW_KEY_UP]) { // If up arrow
            camera.ProcessKeyboard(DOWNPITCH, deltaTime); // Move camera in negative pitch with callback
        } else if (keys[GLFW_KEY_RIGHT]) { // If right arrow
            camera.ProcessKeyboard(UPYAW, deltaTime); // Move camera in positive yaw with callback
        } else if (keys[GLFW_KEY_LEFT]) { // If left arrow
            camera.ProcessKeyboard(DOWNYAW, deltaTime); // Move camera in negative yaw with callback
        }
    }
    else if (keys[GLFW_KEY_RIGHT]) { // If right arrow
        camera.ProcessKeyboard(RIGHT, deltaTime); // Translate camera right with callback
    }
    else if (keys[GLFW_KEY_LEFT]) { // If left arrow
        camera.ProcessKeyboard(LEFT, deltaTime); // Translate camera left with callback
    }
    else if (keys[GLFW_KEY_UP]) { // If up arrow
        camera.ProcessKeyboard(UP, deltaTime); // Translate camera up with callback
    }
    else if (keys[GLFW_KEY_DOWN]) { // If down arrow
        camera.ProcessKeyboard(DOWN, deltaTime); // Translate camera down with callback
    }
    else if (keys[GLFW_KEY_R]) { // If r is pressed
        camera.ResetCamera(); // Reset camera with callback
    }
}
