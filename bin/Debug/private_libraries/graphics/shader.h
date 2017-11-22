#pragma once
#include <vector>
#include <iostream>
#include "../utils//fileutils.h"
#include <GL/glew.h>
#include "../maths/maths.h"
namespace Erebos{
	namespace graphics{

		class Shader
		{
		private:
			GLuint m_ShaderID;
			const char* m_VertPath, *m_FragPath;

		public: 
			//Shader(const char* vertPath, const char* fragPath);
			Shader();
			~Shader();


			void setUniform1f(const GLchar* name, float value);
			void setUniform1i(const GLchar* name, int value);
			void setUniform2f(const GLchar* name, const maths::vec2& vector);
			void setUniform3f(const GLchar* name, const maths::vec3& vector);
			void setUniform4f(const GLchar* name, const maths::vec4& vector);
			void setUniformMat4(const GLchar* name, const maths::mat4& matrix);




			void Initialise_shader(const char* vertPath, const char* fragPath);
			void enable() const;
			void disable() const;

		public:
			GLint getUniformLocation(const GLchar* name);
			GLuint load();
		};

	}
}