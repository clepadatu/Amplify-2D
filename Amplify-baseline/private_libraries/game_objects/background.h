#pragma once
#include "GameObject.h"


namespace Erebos{
	namespace graphics{
		using	namespace	maths;

		class Background : public GameObject
			{
			protected:
				float position_x;
				float position_y;
				const char* texture_path;
			public:
				Background ( Window* window, GLfloat vertices [12], GLushort indices [6], GLfloat colors [16], GLfloat texture_coords [8],const char* tex );
				void Initialise_texture ();
				void Initialise_controls ();
				void To_screen ();


				bool fade_in;
				bool fade_out;
				float min_alpha;
				float max_alpha;
				float active_alpha;
				float step;//0.00005

				void Update ();
			};



		}
	}
