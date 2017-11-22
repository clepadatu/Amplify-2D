#pragma once
#include <iostream>
#include <GL/glew.h>//GL EXTENDED WINDOWS, OpenGL v5.4
#include <GLFW/glfw3.h>//GL FOR WINDOWS, OpenGL v1.0


namespace Erebos {
	namespace graphics{



#define MAX_KEYS 1024
#define MAX_BUTTONS 32
		class Window;
		class Input: public Window
		{

		private:

			static bool m_Keys[MAX_KEYS];
			static bool M_MouseButtons[MAX_BUTTONS];
			static double m_Mx, m_My;

		private:
			friend void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

		};



	}
}
