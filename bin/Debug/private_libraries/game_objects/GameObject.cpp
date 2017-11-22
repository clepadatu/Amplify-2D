#include	"GameObject.h"

namespace Erebos{
	namespace graphics{
		using	namespace	maths;
		GameObject::GameObject()

		{	
			
		};
		void GameObject::set_vars(Window* window, GLfloat vertices[12], GLushort indices[6], GLfloat colors[16], GLfloat texture_coords[8])
		{
			Main_window = window;
			O_vertices = vertices;
			O_indices = indices;
			O_colors = colors;
			O_texture_coordinates = texture_coords;
			
			Object_ibo.set_properties(O_indices, 6);
			Object.addBuffer(new Buffer(O_vertices, 4 * 3, 3), 0);
			Object.addBuffer(new Buffer(O_colors, 4 * 4, 4), 1);
			Object.addBuffer(new Buffer(O_texture_coordinates, 4 * 2, 2), 2);

			Initialise_texture();

		}
		void GameObject::Initialise_controls()
		{
			window_width = Main_window->getWidth();
			window_height = Main_window->getHeight ( );
			Main_window->getMousePosition ( mouse_x, mouse_y );
			type = 0;
			Object_controls.set_init(window_width, window_height, type, mouse_x, mouse_y);
		};

	
		void GameObject::Initialise_texture()
		{
			glGenTextures(1, &O_texture);
			glBindTexture(GL_TEXTURE_2D, O_texture);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			
			unsigned char* image = SOIL_load_image("private_libraries/textures/shship.png", &O_texture_width, &O_texture_height, 0, SOIL_LOAD_RGBA);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, O_texture_width, O_texture_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
			glGenerateMipmap(GL_TEXTURE_2D);
			SOIL_free_image_data(image);
			glBindTexture(GL_TEXTURE_2D, 0);

			
		};

		void GameObject::Compute_movement()
		{	
			if (Check_resize())
				Initialise_controls();

			Main_window->getMousePosition ( mouse_x, mouse_y );
			//std::cout << "(X,Y)   =   " << mouse_x << "," << mouse_y << std::endl;
			Object_controls.computeMatricesFromInputs(Main_window, mouse_x, mouse_y);
			
		};

		void GameObject::Compute_matrices()
		{
			glm::mat4 MVP = Object_controls.getProjectionMatrix() * Object_controls.getViewMatrix()*Object_controls.getModelMatrix();
			glUniformMatrix4fv(Object_shader.getUniformLocation("MVP"), 1, GL_FALSE, &MVP[0][0]);
		}


		void GameObject::Enable_shader()
		{
			Object_shader.Initialise_shader("private_libraries/shaders/basic.vert", "private_libraries/shaders/basic.frag");
			Object_shader.enable();
		}

		void GameObject::bind()
		{
			
			Object.bind();
			Object_ibo.bind();
			
		};
		void GameObject::unbind()
		{
			Object_ibo.unbind();
			Object.unbind();
		};
		void GameObject::texture_activate()
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, O_texture);
			glUniform1i(Object_shader.getUniformLocation("Ship_texture"), 0);
		};

		GLuint GameObject::ibo_count()
		{
			return Object_ibo.getCount();
		};
		
		void GameObject::Draw()
		{
			glDrawElements(GL_TRIANGLES, ibo_count(), GL_UNSIGNED_SHORT, (void*)0);
		}
		
		bool GameObject::Check_resize()
		{
		if ( window_width != Main_window->getWidth ( ) )
				return 1;
		if ( window_height != Main_window->getHeight ( ) )
				return 1;
			return 0;
		}

		void GameObject::To_screen()
		{}
		void GameObject::Update ()
			{

			}
		GameObject::~GameObject ()
			{
			//delete Main_window;
			}

	}
}
