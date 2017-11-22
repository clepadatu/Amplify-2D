#include "controls_MVP.h"

using namespace Erebos;
using namespace graphics;

		glm::mat4 Controls_MVP::getProjectionMatrix()
		{
			return ProjectionMatrix;
		}
		glm::mat4 Controls_MVP::getViewMatrix()
		{
			return ViewMatrix;
		}
		glm::mat4 Controls_MVP::getModelMatrix()
		{
			return ModelMatrix;
		}

		void Controls_MVP::computeMatricesFromInputs(Window* win)
		{
			double currentTime = glfwGetTime();
			
			float deltaTime = float(currentTime - lastTime);

			
			//Aleft - move cube axis x
			if (win->isKeyPressed(263)){


				//camera += glm::vec3(0, speed*deltaTime, speed*deltaTime);
				MM_transform = glm::translate(MM_transform, glm::vec3(-speed*deltaTime, 0, 0));
					

			}
			//Aright - Move cube axis x
			if (win->isKeyPressed(262)){


				//camera -= glm::vec3(0, speed*deltaTime, speed*deltaTime);
				MM_transform = glm::translate(MM_transform, glm::vec3(+speed*deltaTime, 0, 0));
			}

			// KP4 - rotate around
			if (win->isKeyPressed(324)){
				
				
				camera += glm::vec3(speed*deltaTime, 0, 0);
				//look += glm::vec3(speed*deltaTime, speed*deltaTime, speed*deltaTime);
				
			}
			// KP6 - rotate around
			if (win->isKeyPressed(326)){
				
				camera -= glm::vec3(speed*deltaTime, 0,0 );
				//look -= glm::vec3(speed*deltaTime, speed*deltaTime, speed*deltaTime);
			}
			// pagedown = go towards yourself - camera is moving
			if (win->isKeyPressed(267)){
				camera += deltaTime * speed;
			}
			// pageup = go towards origin - camera is moving
			if (win->isKeyPressed(266)){
				camera -= deltaTime * speed;
			}

			// Direction : Spherical coordinates to Cartesian coordinates conversion


			// Up vector : perpendicular to both direction and right
			

			// Projection matrix : 45&deg; Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
			ProjectionMatrix = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.0f, 100.0f); // In world coordinates
			// Camera matrix
			ViewMatrix = glm::lookAt(
				camera, // Camera is at (4,3,3), in World Space
				look, // and looks at the origin
				head// Head is up (set to 0,-1,0 to look upside-down)
				);

			ModelMatrix *= MM_transform;
			MM_transform=glm::mat4(1.0);
			lastTime = currentTime;

		}


