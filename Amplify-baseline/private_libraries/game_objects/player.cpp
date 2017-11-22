#include "player.h"

Player::Player ( Window* window, GLfloat vertices [12], GLushort indices [6], GLfloat colors [16], GLfloat texture_coords [8] )
	{
	Main_window = window;
	O_vertices = vertices;
	O_indices = indices;
	O_colors = colors;
	O_texture_coordinates = texture_coords;

	Object_ibo.set_properties ( O_indices, 6 );
	Object.addBuffer ( new Buffer ( O_vertices, 4 * 3, 3 ), 0 );
	Object.addBuffer ( new Buffer ( O_colors, 4 * 4, 4 ), 1 );
	Object.addBuffer ( new Buffer ( O_texture_coordinates, 4 * 2, 2 ), 2 );

	Initialise_texture ( );

	}
void Player::To_screen()
{
Object_shader.enable ( );
this->Compute_matrices ( );
	this->bind();
	this->texture_activate();


	this->Draw();
	this->unbind();
}

void Player::Update ()
{
this->Compute_movement ( );


}

bool Player::check_click()
{
	if (Object_controls.check_click(Main_window))
		return true;
	else
		return false;
}

glm::vec2 Player::get_direction_for_bullet()
{
	float origin_x = Object_controls.getPlayerX();
	float origin_y = Object_controls.getPlayerY();
	glm::vec2 projectile_direction = glm::vec2(origin_x, 1.0f) - glm::vec2(origin_x, origin_y);
	projectile_direction = glm::normalize(projectile_direction);
	return projectile_direction;
	
}
glm::vec2 Player::get_player_position()
{
	float origin_x = Object_controls.getPlayerX();
	float origin_y = Object_controls.getPlayerY();
	return glm::vec2(origin_x, origin_y);
}
