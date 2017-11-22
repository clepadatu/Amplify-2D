#pragma once
#include "GameObject.h"


namespace Erebos{
	namespace graphics{
		using	namespace	maths;

		class Player : public GameObject
		{
		public:
			bool check_click();
			glm::vec2 get_direction_for_bullet();
			glm::vec2 get_player_position();
			Player ( Window* window, GLfloat vertices [12], GLushort indices [6], GLfloat colors [16], GLfloat texture_coords [8] );
			void Update ();
			void To_screen();
			
		};



	}
}
