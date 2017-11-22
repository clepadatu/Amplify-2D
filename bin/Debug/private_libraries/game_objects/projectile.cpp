#include "projectile.h"


Projectile::~Projectile ()
	{

	}

void Projectile::Reinit_pos ( glm::vec2 pos )
	{
	projectile_position = pos;
	}

void Projectile::Initialise_controls ( )
	{
	
	window_width = Main_window->getWidth ( );
	window_height = Main_window->getHeight ( );
	Main_window->getMousePosition ( mouse_x, mouse_y );
	type = 0;

	//std::cout << "Projectile id=" << this->PID << ", at (x,y)=" << projectile_position.x << "," << projectile_position.y << std::endl;
	//Object_controls.set_init_and_pos ( window_width, window_height, type, mouse_x, mouse_y, projectile_position.x, projectile_position.y );
	Object_controls.set_init_and_pos_and_size ( window_width, window_height, type, mouse_x, mouse_y, projectile_position.x, projectile_position.y,50.0f,50.0f,50.0f );
	}

void Projectile::Initialise_texture ( )
	{
	glGenTextures ( 1, &O_texture );
	glBindTexture ( GL_TEXTURE_2D, O_texture );
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER );
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER );
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );


	unsigned char* image = SOIL_load_image ( "private_libraries/textures/fireball.png", &O_texture_width, &O_texture_height, 0, SOIL_LOAD_RGBA );
	glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGBA, O_texture_width, O_texture_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image );
	glGenerateMipmap ( GL_TEXTURE_2D );
	SOIL_free_image_data ( image );
	glBindTexture ( GL_TEXTURE_2D, 0 );
	}
void Projectile::Compute_matrices ( )
	{
	//this->update_projectile ( );
	glm::mat4 MVP = Object_controls.getProjectionMatrix ( ) * Object_controls.getViewMatrix ( )*Object_controls.getModelMatrix ( );
	//std::cout << "Projectile id=" << this->PID << ", moved to (x,y)=" << projectile_position.x << "," << projectile_position.y << std::endl;
	MVP [3][0] = projectile_position.x;
	MVP [3][1] = projectile_position.y;
	glUniformMatrix4fv ( Object_shader.getUniformLocation ( "MVP" ), 1, GL_FALSE, &MVP [0][0] );
	}

void Projectile::_To_screen ( )
	{
	for ( int times = 0; times < steps; times++ )
		{
		this->update_projectile ();
		steps--;
		}
	//std::cout << this->PID << " is at coords(x,y):  " << Object_controls.return_obj_x()<<","<<Object_controls.return_obj_y()<<",size:  "<<Object_controls.return_size_x()<<","<<Object_controls.return_size_y()<< std::endl;
	Object_shader.enable ( );
    this->Compute_matrices ();
		

	this->bind ( );
	this->texture_activate ( );


	this->Draw ( );
	this->unbind ( );

	}

bool Projectile::_Should_draw ()
{
	if ( active==false )
		{
		//active = false;
		window_width = Main_window->getWidth ( );
		window_height = Main_window->getHeight ( );
		this->Reinit_pos ( glm::vec2 ( window_width, window_height ) );
		//std::cout << this->PID << " is done executing, because liftime=" << projectile_lifetime << std::endl;
		return false;
		};
	//std::cout << "alive" << std::endl;
	return true;
	
}

void Projectile::update_projectile()
{


	projectile_position += projectile_direction*projectile_speed;
	
	
	if ( projectile_position.y > 1 )
		{
		active = false;
		
		}

	
}

Projectile::Projectile ( glm::vec2 pos, glm::vec2 dir, float speed, int lifetime, double suid )
	{
	//std::cout << "initial mouse pos indicated=" << pos.x<<","<<pos.y << std::endl;
	projectile_position = pos;
	projectile_direction = dir;
	projectile_speed = speed;
	projectile_lifetime = lifetime;
	uid = suid;
	active = false;
	steps = 0;
	
	PID = rand ( ) % 10000 + 1;
	}

bool Projectile::operator==(const Projectile& other)
	{
	if ( this->uid == other.uid )
		{
		if (this->projectile_lifetime<=0)
			return true;
		}
	return false;
	}