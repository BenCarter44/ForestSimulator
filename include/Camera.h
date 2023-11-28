#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h> // Glew include
#include <glm/glm.hpp> // GLM include
#include <glm/gtc/matrix_transform.hpp> // Matrix transform include

#include <vector> // Include vector

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
	FORWARD, // Allow forward camera movement [z]
	BACKWARD, // Allow backward camera movement [z]
	LEFT, // Move along x-axis
	RIGHT, // Move along x-axis
	UP, // Move along y-axis
	DOWN, // Move along y-axis
	UPPITCH, // Rotate pitch positive
	DOWNPITCH, // Rotate pitch negative
	UPYAW, // Rotate yaw positive
	DOWNYAW, // Rotate yaw negative
	UPROLL, // Rotate roll positive
	DOWNROLL // Rotate roll negative
};

// Default camera values
const float YAW = -90.0f; // Initialize yaw [flip screen to normal]
const float PITCH = 0.0f; // Initailize pitch
const float ROLL = 0.0f; // Initialize roll
const float SPEED = 2.5f; // Initialize speed


// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera
{
public:
	// Camera Attributes
	glm::vec3 Position; // Position vector
	glm::vec3 Front; // Front dir vector
	glm::vec3 Up; // Up dir vector
	glm::vec3 Right; // Right dir vector
	glm::vec3 WorldUp; // WorldUp vector
	// Euler Angles
	float Yaw; // yaw
	float Pitch; // pitch
	float Roll; // roll
	// Camera options
	float MovementSpeed; // speed for translation

	// Constructor with vectors
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH, float roll = ROLL) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED)
	{
		Position = position; // Set position based on input
		WorldUp = up; // Set up reference based on input
		Yaw = yaw; // Set yaw based on input
		Pitch = pitch; // Set pitch based on input
		Roll = roll; // Set roll based on input
		updateCameraVectors(); // Call class method to set front, right, and up vectors
	}
	// Constructor with scalar values
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch, float roll) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED)
	{
		Position = glm::vec3(posX, posY, posZ); // Set position elements manually from input
		WorldUp = glm::vec3(upX, upY, upZ); // Set WorldUp elements manually from input
		Yaw = yaw; // Set yaw based on input
		Pitch = pitch; // Set pitch based on input
		Roll = roll; // Set roll based on input
		updateCameraVectors(); // Call class method to set front, right, and up vectors
	}

	// Returns the view matrix calculated using Euler Angles and the LookAt Matrix
	glm::mat4 GetViewMatrix()
	{
		return glm::lookAt(Position, Position + Front, Up); // Returns lookAt output using Posiiton, Position + Front, and Up
	}

	// Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
	void ProcessKeyboard(Camera_Movement direction, float deltaTime)
	{
		// Defines all directions
		float velocity = MovementSpeed * deltaTime; // Calculate velocity using speed and time
		if (direction == FORWARD) // If forward direction
			Position += Front * velocity; // Add front * velocity to position
		if (direction == BACKWARD) // If backward
			Position -= Front * velocity; // Subtract front * velocity from position
		if (direction == LEFT) // If left
			Position -= Right * velocity; // Subtract Right * velocity from position
		if (direction == RIGHT) // If right
			Position += Right * velocity; // Add right * velocity to position
		if (direction == UP) // If up
			Position += Up * velocity; // Add up * velocity to position
		if (direction == DOWN) // If down
			Position -= Up * velocity; // Subtract up * velocity to position
		if (direction == UPPITCH) // If up pitch
			Pitch += 2.0f; // Increment pitch by 2 [degrees]
			updateCameraVectors(); // Update rotation using callback
		if (direction == DOWNPITCH) // If down pitch
			Pitch -= 2.0f; // Decrement pitch by 2 [degrees]
			updateCameraVectors(); // Update rotation using callback
		if (direction == UPYAW) // If up yaw
			Yaw += 2.0f; // Increment yaw by 2 [degrees]
			updateCameraVectors(); // Update rotation using callback
		if (direction == DOWNYAW) // If down yaw
			Yaw -= 2.0f; // Decrement yaw by 2 [degrees]
			updateCameraVectors(); // Update rotation using callback
		if (direction == UPROLL) // If up roll
			Roll += 2.0f; // Increment roll by 2 [degrees]
			updateCameraVectors(); // Update rotation using callback
		if (direction == DOWNROLL) // If down roll
			Roll -= 2.0f; // Decrement roll by 2 [degrees]
			updateCameraVectors(); // Update rotation using callback
	}

	// Resets camera position and rotation vectors
	void ResetCamera() {
		Position = glm::vec3(0.0f, 0.0f, 0.0f); // Resets position
		WorldUp = glm::vec3(0.0f, 1.0f, 0.0f); // Resets worldup vector
		Yaw = YAW; // Resets yaw
		Pitch = PITCH; // Resets pitch
		Roll = ROLL; // Resets roll
		updateCameraVectors(); // Updates rotation with reset values using callback
	}

private:
	// Calculates the front vector from the Camera's (updated) Euler Angles
	void updateCameraVectors()
	{
		// Calculate the new Front vector
		glm::vec3 front; // Initialize front
		front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch)); // Define x value for front using cos(Yaw) * cos(Pitch)
		front.y = sin(glm::radians(Pitch));// Define y value for front using sin(pitch)
		front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch)); // Define z value for front using sin(Yaw) * cos(Pitch)
		Front = glm::normalize(front); // Normalize vector
		// // Also re-calculate the Right and Up vector --> normalize right and up and cross product with Front
		Right = glm::normalize(glm::cross(Front, WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		Up = glm::normalize(glm::cross(Right, Front)); // Normalize the cross product of Right and Front
		Up.x = sin(glm::radians(Roll)); // Set x of Up to sin(Roll)
		Up.y = cos(glm::radians(Roll)); // Set y of Up to cos(Roll)
		Up = glm::normalize(Up); // Normalize new Up
		Right = glm::normalize(glm::cross(Front, Up)); // Reset Right to reflect new Up axis vector
	}
};
#endif
