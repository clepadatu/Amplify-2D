#include "AI_controls.h"

using namespace Erebos;
using namespace graphics;

/*AI_Controls::AI_Controls(int	width, int		height, int		type, double x, double y) : _width(width), _height(height), _type(type), mouse_x_last(x), mouse_y_last(y)
{
ProjectionMatrix	=	glm::ortho	(0.0f,	float(_width),	float(_height),	0.0f,	1.0f,	-1.0f); // In world coordinates, left,right,bottom,top,near,far
TranslationMatrix	=	glm::translate	(glm::mat4(1.0f),	glm::vec3(xpos,ypos,0.0f));
ModelMatrix		=	    glm::scale	(TranslationMatrix,		glm::vec3(60.0f, 60.0f,60.0f));

//maybe



}*/
AI_Controls::AI_Controls(){};

void AI_Controls::set_init(int	width, int		height, int		type, double x, double y)
{
	_width = width;
	_height = height;
	_type = type;
	mouse_x_last = x;
	mouse_y_last = y;
	ProjectionMatrix = glm::ortho(0.0f, float(_width), float(_height), 0.0f, 1.0f, -1.0f); // In world coordinates, left,right,bottom,top,near,far
	TranslationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(xpos, ypos, 0.0f));
	ModelMatrix = glm::scale(TranslationMatrix, glm::vec3(60.0f, 60.0f, 60.0f));

}

glm::mat4 AI_Controls::getProjectionMatrix()
{
	return	ProjectionMatrix;
}
glm::mat4 AI_Controls::getViewMatrix()
{
	return	ViewMatrix;
}
glm::mat4 AI_Controls::getModelMatrix()
{
	return	ModelMatrix;
}

void AI_Controls::computeMatrices()
{
	//ModelMatrix = obj_move*ModelMatrix;
}


void AI_Controls::computeMatricesFromInputs(Window* win, double x, double y)
{


	//win->getMousePosition(x, y); maybe
	if (mouse_x_last != x && mouse_y_last != y)
	{
		TranslationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0.0f));
		ModelMatrix = glm::scale(TranslationMatrix, glm::vec3(60.0f, 60.0f, 60.0f));
		mouse_x_last = x;
		mouse_y_last = y;
	}



	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);
	TempMatrix = ProjectionMatrix*ViewMatrix*ModelMatrix;
	xpos = TempMatrix[3][0];
	ypos = TempMatrix[3][1];


	//Aleft - move cube axis x
	if (win->isKeyPressed(263) && xpos>-1.0f){


		//camera += glm::vec3(0, speed*deltaTime, speed*deltaTime);
		//rotation command
		//ModelMatrix = glm::rotate(ModelMatrix, speed*deltaTime, glm::vec3(0, 0, -1));

		std::cout << "Current Xposition is: " << xpos << std::endl;
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(-speed*deltaTime, 0, 0));

	}
	//Aright - Move cube axis x
	if (win->isKeyPressed(262) && xpos<1.0f){


		//camera -= glm::vec3(0, speed*deltaTime, speed*deltaTime);
		//rotation command
		//ModelMatrix = glm::rotate(ModelMatrix, speed*deltaTime, glm::vec3(0, 0, 1));

		std::cout << "Current Xposition is: " << xpos << std::endl;
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(speed*deltaTime, 0, 0));

	}


	//Adown - Move cube axis x
	if (win->isKeyPressed(264) && ypos>-1){


		//camera -= glm::vec3(0, speed*deltaTime, speed*deltaTime);
		//ModelMatrix = glm::translate(ModelMatrix, glm::vec3(-speed*deltaTime, 0, 0));
		std::cout << "Current Yposition is: " << ypos << std::endl;
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0, speed*deltaTime, 0));
	}

	//Aup - Move cube axis x
	if (win->isKeyPressed(265) && ypos<1){


		//camera -= glm::vec3(0, speed*deltaTime, speed*deltaTime);
		//ModelMatrix = glm::translate(ModelMatrix, glm::vec3(speed*deltaTime, 0, 0));
		std::cout << "Current Yposition is: " << ypos << std::endl;
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0, -speed*deltaTime, 0));
	}

	if (win->isKeyPressed(32))
	{
		space_pressed = 1;
	}

	if (space_pressed == 1)
	{
		std::cout << "Current Yposition is: " << ypos << std::endl;
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0, -speed*deltaTime, 0));
	}

	if (win->isKeyPressed(256))
	{
		space_pressed = 0;
	}

	// KP4 - rotate around
	if (win->isKeyPressed(324)){


		//	MM_transform = glm::rotate(glm::radians(step), glm::vec3(0, 0, 1));
		//camera += glm::vec3(speed*deltaTime, 0, 0);
		//look += glm::vec3(speed*deltaTime, speed*deltaTime, speed*deltaTime);

	}
	// KP6 - rotate around
	if (win->isKeyPressed(326)){

		//MM_transform = glm::rotate(glm::radians(step), glm::vec3(0, 0,-1));
		//camera -= glm::vec3(speed*deltaTime, 0, 0);
		//look -= glm::vec3(speed*deltaTime, speed*deltaTime, speed*deltaTime);
	}
	// pagedown = go towards yourself - camera is moving
	if (win->isKeyPressed(267)){
		//		camera += deltaTime * speed;
	}
	// pageup = go towards origin - camera is moving
	if (win->isKeyPressed(266)){
		//	camera -= deltaTime * speed;
	}

	computeMatrices();

	lastTime = currentTime;

}


/*if (x != _x && y != _y)
{
ModelMatrix = glm::translate(ModelMatrix, glm::vec3(float((x - _x) / 100), float((y - _y) / 100), 0.0f));
_x = x;
_y = y;
}*/