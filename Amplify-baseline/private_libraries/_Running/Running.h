#pragma once
#include "../window/window.h"
#include <string>

#include	"../utils/fileutils.h"
#include	"../graphics/shader.h"
#include	"../graphics/buffers/buffer.h"
#include	"../graphics/buffers/indexbuffer.h"
#include	"../graphics/buffers/vertexarray.h"
#include	<glm.hpp>
#include	<gtc/matrix_transform.hpp>
#include	<gtx/transform.hpp>
#include	<chrono>
#include	"..\utils\controls_MVP.h"
#include	"..\utils\controls_MP.h"
#include	<SOIL.h>
#include	"..\game_objects\GameObject.h"
#include	"..\game_objects\player.h"
#include	"..\game_objects\AI.h"
#include	"..\game_objects\projectile.h"
#include	"..\game_objects\background.h"
#include	"..\game_objects\textobject.h"
#include    <list>
#include <irrKlang.h>
#include <memory>
#include "Layer.h"

namespace Erebos
	{
	namespace graphics{
		using namespace irrklang;
	

		class Running
			{
			public:

				Layer* Amplify_Layer;
				Window* Core_window;
				std::string Menu_name;
				bool Enemies;    // AI Toggle
				int Enemies_count; // number of AI instances
				bool Human;    // Human Toggle
				bool Input;	   // Keyboard Input Toggle
				const char* bg_tex;
				const char* AI_tex;

				int Core_window_width, Core_window_height; // (X,y)
				bool Core_window_state;

				GLfloat		vertices_square [12];
				GLfloat		vertices_rectangle [20];
				GLushort	indices_square [6];
				GLushort	 indices_rectangle [6];
				GLfloat		colorsA [16];
				GLfloat		colorsB [16];
				GLfloat texture_coordinates [8];


				Player* Player1;
				AI* AI1;
				AI* AI2;
				int AIs_remaining;
				double uidz;
				std::list<Projectile> ammo;
				std::list<AI> AIs;
				
				Background* Background1;
				TextObject* Text;
				
				int number_of_bullets;
				int max_bullets;

				ISoundEngine* SoundEngine;
				irrklang::ISoundSource* shootSound;
				irrklang::ISoundSource* maintheme;

				float current_score;
				float projectiles_used;
				float multiplier;
				float AI_value;
				std::string Playername;
				std::vector<std::string> Highscores;
			public:

				bool all_registered;
				bool score_saved;
				Running (Layer* Layer);
				~Running ();
				bool is_on (); //game-loop checker
				void GLHelpers_Init ();
				void Set_Amplify_Visuals ( );
				void Amplify_Visuals ();
				//	void process_input ();
				//void update_game_state ();
				void update_graphics (double elapsed); //render to screen
				void launch_projectile ();
				void display_projectiles ();
				void display_enemies ();
				void update_projectiles ();
				void update_enemies ();
				GLboolean CheckCollision ( AI &one, Projectile &two );
				void DoCollisions ();
				int AI_remaining ();
				void Update_Score ();
				void Reset_Score ();
			};

	
		}
	}