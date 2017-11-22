#pragma	once
#include <vector>
#include <iostream>
#include <GL/glew.h>
#include	"../graphics/buffers/buffer.h"
#include	"../graphics/buffers/indexbuffer.h"
#include "../graphics/buffers/vertexarray.h"
#include <SOIL.h>
#include	"../graphics/shader.h"
#include	"../utils/controls_MVP.h"
#include	"../utils/controls_MP.h"
#include	"../window/window.h"
#include	<glm.hpp>
#include	<gtc/matrix_transform.hpp>
#include	<gtx/transform.hpp>

namespace Erebos{
	namespace graphics{
		using	namespace	maths;
		class GameObject
		{
		public:

			VertexArray Object;
			IndexBuffer Object_ibo;
			Shader Object_shader;
			Window* Main_window;
			Controls_MP	Object_controls; 
			GLfloat* O_vertices;
			GLushort* O_indices;
			GLfloat* O_colors;
			GLfloat* O_texture_coordinates;

			GLuint O_texture;
			int O_texture_width;
			int O_texture_height;

			
			int window_width;
			int window_height;
			int type;

			double mouse_x;
			double mouse_y;
		public:
			
			GameObject();
			~GameObject ();

			virtual void set_vars(Window* window, GLfloat vertices[12], GLushort indices[6], GLfloat colors[16], GLfloat texture_coords[8]);
			
			virtual void Initialise_texture();
			virtual void Initialise_controls();
			virtual void Enable_shader();
			virtual bool Check_resize();
			virtual void Compute_movement();
			virtual void Compute_matrices();
			virtual void bind();
			virtual void Draw();
			virtual void unbind();
			virtual void texture_activate();
			virtual GLuint ibo_count();
			
			virtual void Update ();
			virtual void To_screen();
			


		};

	}
}
