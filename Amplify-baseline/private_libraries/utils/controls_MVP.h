#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtx/transform.hpp>
#include <chrono>
#include <GL/glew.h>//GL EXTENSION WRANGLER, OpenGL v5.4
#include <GLFW/glfw3.h>//GL FOR WINDOWS, OpenGL v1.0
#include "../window/window.h"


using namespace Erebos;
using namespace graphics;
		
	class Controls_MVP{
			// position
			private:
					
					glm::vec3 position = glm::vec3(4, 3, 3);
					glm::mat4 ProjectionMatrix;
					glm::mat4 ViewMatrix;
					glm::mat4 ModelMatrix=glm::mat4(1.0);
					glm::mat4 MM_transform;
					
					glm::vec3 camera = glm::vec3(4, 3, 3);
					glm::vec3 look = glm::vec3(0, 0, 0);
					glm::vec3 head = glm::vec3(0, 1, 0);
					glm::vec3 test = glm::vec3(0, 0, 1);
					// horizontal angle : toward -Z
					float horizontalAngle = 3.14f;
					// vertical angle : 0, look at the horizon
					float verticalAngle = 0.0f;
					// Initial Field of View
					float initialFoV = 45.0f;
					float speed = 5.0f; // 3 units / second kb

					float lastTime = 0;


			public:

					glm::mat4 getProjectionMatrix();
					glm::mat4 getViewMatrix();
					glm::mat4 getModelMatrix();
					void computeMatricesFromInputs(Window* win);
		
				};