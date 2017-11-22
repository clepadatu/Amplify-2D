#include "Background.h"

Background::Background ( Window* window, GLfloat vertices [12], GLushort indices [6], GLfloat colors [16], GLfloat texture_coords [8], const char* tex )
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

	Initialise_texture ( );
	//fade_in=false;
	//fade_out=false;
	//min_alpha=0.0f;
	//max_alpha=1.0f;
	//active_alpha=1.0f;
	//step=0.00005;//0.00005
	}

void Background::Update ()
	{
	
	
	}

void Background::Initialise_texture ( )
	{
	glGenTextures ( 1, &O_texture );
	glBindTexture ( GL_TEXTURE_2D, O_texture );
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER );
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER );
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );


	unsigned char* image = SOIL_load_image ( texture_path, &O_texture_width, &O_texture_height, 0, SOIL_LOAD_RGBA );
	glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGBA, O_texture_width, O_texture_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image );
	glGenerateMipmap ( GL_TEXTURE_2D );
	SOIL_free_image_data ( image );
	glBindTexture ( GL_TEXTURE_2D, 0 );


	};

void Background::Initialise_controls ( )
	{
	window_width = Main_window->getWidth ( );
	window_height = Main_window->getHeight ( );
	Main_window->getMousePosition ( mouse_x, mouse_y );
	type = 0;
	//Object_controls.set_init ( window_width, window_height, type, mouse_x, mouse_y );
	Object_controls.set_init_and_pos_and_size ( window_width, window_height, type, mouse_x, mouse_y,245.0f,245.0f,1920,1080,90.0f );
	};

void Background::To_screen ( )
	{
	Object_shader.enable ( );
	this->Compute_matrices ( );
	this->bind ( );
	this->texture_activate ( );
	this->Draw ( );
	this->unbind ( );
	}