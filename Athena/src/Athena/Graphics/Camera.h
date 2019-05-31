#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Input.h"
#include "Platform/Windows/Window.h"

#include <vector>
namespace ath {
	// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
	enum Camera_Movement {
		FORWARD = 1,
		BACKWARD = 0,
		LEFT = 2,
		RIGHT = 3
	};

	// Default camera values
	const float YAW = -90.0f;
	const float PITCH = 0.0f;
	const float SPEED = 2.5f;
	const float SENSITIVITY = 0.1f;
	const float ZOOM = 45.0f;


	// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
	class ATHENA_API Camera {
	public:
		// Camera Attributes
		glm::vec3 Position;
		glm::vec3 Front;
		glm::vec3 Up;
		glm::vec3 Right;
		glm::vec3 WorldUp;
		// Euler Angles
		float Yaw;
		float Pitch;
		// Camera options
		float MovementSpeed;
		float MouseSensitivity;
		float Zoom;

	private:
		unsigned int window_width = ATH_INITIAL_WIDTH;
		unsigned int window_height = ATH_INITIAL_HEIGHT;

		bool firstMouse = true;
		float lastY = 0;
		float lastX = 0;
		float deltaTime = 0.0f;
		float lastFrame = 0.0f;

		bool * directions;

	public:

		static Camera & getInstance() {
			static Camera instance; // Guaranteed to be destroyed
			return instance;        // Instantiated on first use.
		}

		// Returns the view matrix calculated using Euler Angles and the LookAt Matrix
		glm::mat4 GetViewMatrix() {
			return glm::lookAt(Position, Position + Front, Up);
		}

		glm::mat4 GetProjectionMatrix() {
			return glm::perspective(glm::radians(this->Zoom), (float)this->window_width /
				(float)this->window_height, 0.1f, 250.0f);
		}

		void SynchronizeWindowsSize(unsigned int width, unsigned int height) {
			window_width = width;
			window_height = height;
			glViewport(0, 0, width, height);
		}

		void Update() {
			float currentFrame = glfwGetTime();
			this->deltaTime = currentFrame - this->lastFrame;
			this->lastFrame = currentFrame;

			if (Input::IsKeyReleased(GLFW_KEY_W))
				this->directions[FORWARD] = false;
			if (Input::IsKeyReleased(GLFW_KEY_S))
				this->directions[BACKWARD] = false;
			if (Input::IsKeyReleased(GLFW_KEY_A))
				this->directions[LEFT] = false;
			if (Input::IsKeyReleased(GLFW_KEY_D))
				this->directions[RIGHT] = false;

			for (int i = 0; i < 4; i++)
				if (this->directions[i])
					this->ProcessKeyboard((Camera_Movement)i);
		}

		// Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
		void ProcessKeyboard(Camera_Movement direction) {

			float velocity = this->MovementSpeed * this->deltaTime;

			if (direction == FORWARD)
				this->Position += this->Front * velocity;
			if (direction == BACKWARD)
				this->Position -= this->Front * velocity;
			if (direction == LEFT)
				this->Position -= this->Right * velocity;
			if (direction == RIGHT)
				this->Position += this->Right * velocity;
		}

		void move(int key) {
			if (Input::IsKeyPressed(GLFW_KEY_W))
				this->directions[FORWARD] = true;

			if (Input::IsKeyPressed(GLFW_KEY_S))
				this->directions[BACKWARD] = true;

			if (Input::IsKeyPressed(GLFW_KEY_A))
				this->directions[LEFT] = true;

			if (Input::IsKeyPressed(GLFW_KEY_D))
				this->directions[RIGHT] = true;

			//CORE_INFO(key);
		}

		// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
		void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true) {
			xoffset *= MouseSensitivity;
			yoffset *= MouseSensitivity;

			Yaw += xoffset;
			Pitch += yoffset;

			// Make sure that when pitch is out of bounds, screen doesn't get flipped
			if (constrainPitch) {
				if (Pitch > 89.0f)
					Pitch = 89.0f;
				if (Pitch < -89.0f)
					Pitch = -89.0f;
			}

			// Update Front, Right and Up Vectors using the updated Euler angles
			updateCameraVectors();
		}

		void reactToMouseMove(double xPos, double yPos) {

			// first frame espescial
			if (this->firstMouse) {
				this->lastX = xPos;
				this->lastY = yPos;
				this->firstMouse = false;
			}

			// Calculate differences between each frame
			float xoffset = xPos - this->lastX;
			float yoffset = this->lastY - yPos; // reversed since y-coordinates go from bottom to top

			this->lastX = xPos;
			this->lastY = yPos;

			this->ProcessMouseMovement(xoffset, yoffset);
		}

		// Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
		void ProcessMouseScroll(float yoffset) {
			if (Zoom >= 1.0f && Zoom <= 45.0f)
				Zoom -= yoffset;
			if (Zoom <= 1.0f)
				Zoom = 1.0f;
			if (Zoom >= 45.0f)
				Zoom = 45.0f;
		}

	private:
		// Calculates the front vector from the Camera's (updated) Euler Angles
		void updateCameraVectors() {
			// Calculate the new Front vector
			glm::vec3 front;
			front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
			front.y = sin(glm::radians(Pitch));
			front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
			Front = glm::normalize(front);
			// Also re-calculate the Right and Up vector
			Right = glm::normalize(glm::cross(Front, WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
			Up = glm::normalize(glm::cross(Right, Front));
		}

		// Constructor with vectors
		Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, +3.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, -0.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM) {
			Position = position;
			WorldUp = up;
			Yaw = yaw;
			Pitch = pitch;
			updateCameraVectors();

			this->directions = new bool[4];
			for (int i = 0; i < 4; i++)
				this->directions[i] = false;
		}
		// Constructor with scalar values
		Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM) {
			Position = glm::vec3(posX, posY, posZ);
			WorldUp = glm::vec3(upX, upY, upZ);
			Yaw = yaw;
			Pitch = pitch;
			updateCameraVectors();

			this->directions = new bool[4];
			for (int i = 0; i < 4; i++)
				this->directions[i] = false;
		}
	};
}