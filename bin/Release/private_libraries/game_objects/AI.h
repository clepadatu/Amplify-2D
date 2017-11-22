#pragma once
#include "GameObject.h"


namespace Erebos{
	namespace graphics{
		using	namespace	maths;

		class AI : public GameObject
		{
		protected:
			float position_x;
			float position_y;
			const char* texture_path;
		public:
			glm::vec2 position;
			bool destroyed;
			AI ( Window* window, GLfloat vertices [12], GLushort indices [6], GLfloat colors [16], GLfloat texture_coords [8],const char* tex );
			void Initialise_texture();
			void Initialise_controls();
			void Compute_movement_AI();
			void To_screen();
			void Update ();
			
		};



	}
}
