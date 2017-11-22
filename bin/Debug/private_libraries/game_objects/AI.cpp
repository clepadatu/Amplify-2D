#include "AI.h"

AI::AI ( Window* window, GLfloat vertices [12], GLushort indices [6], GLfloat colors [16], GLfloat texture_coords [8], const char* tex )
	{
	Main_window = window;
	O_vertices = vertices;
	O_indices = indices;
	O_colors = colors;
	O_texture_coordinates = texture_coords;
	texture_path = tex;
	Object_ibo.set_properties ( O_indices, 6 );
	Object.addBuffer ( new Buffer ( O_vertices, 4 * 3, 3 ), 0 );
	Object.addBuffer ( new Buffer ( O_colors, 4 * 4, 4 ), 1 );
	Object.addBuffer ( new Buffer ( O_texture_coordinates, 4 * 2, 2 ), 2 );
	destroyed = false;
	Initialise_texture ( );

	}

void AI::Initialise_texture()
{
	glGenTextures(1, &O_texture);
	glBindTexture(GL_TEXTURE_2D, O_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	unsigned char* image = SOIL_load_image(texture_path, &O_texture_width, &O_texture_height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, O_texture_width, O_texture_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);


	
};

void AI::Compute_movement_AI()
{
	Object_controls.computeMatricesAI();
}

void AI::Initialise_controls()
{
window_width = Main_window->getWidth ( );
window_height = Main_window->getHeight ( );
Main_window->getMousePosition ( mouse_x, mouse_y );
	type = 0;

	position_x = rand() % window_width;
	position_y = rand() % (window_height/3)+60;
	Object_controls.set_init_and_pos_and_size ( window_width, window_height, type, mouse_x, mouse_y, position_x, position_y, 50.0f, 50.0f, 50.0f );
}

void AI::To_screen()
{
if ( destroyed == false )
	{
	Object_shader.enable ();
	this->Compute_matrices ();
	this->bind ();
	this->texture_activate ();
	this->Draw ();
	this->unbind ();
	}
}

void AI::Update ()
{
	this->Compute_movement_AI ( );
	position = glm::vec2 ( Object_controls.return_obj_x(), Object_controls.return_obj_y() );

}