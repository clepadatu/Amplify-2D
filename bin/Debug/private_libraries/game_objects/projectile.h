#pragma once
#include "GameObject.h"


namespace Erebos{
	namespace graphics{
		using	namespace	maths;

		class Projectile : public GameObject
		{
		private:
			int projectile_lifetime;
			float projectile_speed;
			float origin_x;
			float origin_y;
			double uid;
			double PID;
			glm::vec2 projectile_direction;
			
		public:
			glm::vec2 projectile_position;
			bool active;
			int steps;
			
			void update_projectile();


			


			void Initialise_controls ( );
			void Initialise_texture ( );
			void Compute_matrices ( );
			void _To_screen ( );
			bool _Should_draw ( );
			Projectile ( glm::vec2 pos, glm::vec2 dir, float speed, int lifetime, double suid );
			~Projectile ( );
			bool operator==(const Projectile& other);
			void Reinit_pos ( glm::vec2 pos );
			void Reset_to_mouse (  );
			/*
			extra tut:
			Projectile();
			~Projectile();

			void init(glm::vec2 pos, glm::vec2 dir, float speed);
			void draw(Bengine::SpriteBatch& spriteBatch);

			
			*/

		};



	}
}
