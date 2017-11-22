#include "Running.h"

namespace Erebos
	{
	namespace graphics{

		Running::Running (Layer* Layer)
			{
			all_registered = false;
			score_saved = false;
			Playername = "";
			projectiles_used = 0;
			multiplier = 0;
			current_score = 0;
			AI_value = 15;
			//Layer Init
			Amplify_Layer = Layer;
			//Window Init
			Core_window_width = 1920;
			Core_window_height = 1080;
			Core_window = new Window ( "Amplify", Core_window_width, Core_window_height );
			Core_window->WindowColor ( 0.0f, 0.0f, 0.0f, 0.3f );
			glEnable ( GL_DEPTH_TEST );
			glDepthFunc ( GL_LEQUAL );
			glEnable ( GL_BLEND );
			//	glEnable ( GL_CULL_FACE );
			glBlendFunc ( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
			glPixelStorei ( GL_UNPACK_ALIGNMENT, 1 );

			//Ship misc Init
			number_of_bullets = 10;
			max_bullets = 10;			
			
			//Sound Init
			SoundEngine = createIrrKlangDevice();
			
			//GL Vertices and Indices data Init
			GLHelpers_Init ();
	
			//Visuals Init
			Set_Amplify_Visuals ();
//			Amplify_Visuals ();
			shootSound = SoundEngine->addSoundSourceFromFile ( "private_libraries/sounds/flaunch.wav" );
			shootSound->setDefaultVolume ( 0.1 );
			maintheme = SoundEngine->addSoundSourceFromFile ( "private_libraries/sounds/themetime.mp3" );
			maintheme->setDefaultVolume ( 1.0 );
			SoundEngine->play2D ( maintheme,GL_TRUE );
			
			}

		void Running::Set_Amplify_Visuals ()
			{

			GLfloat		vertices_square [] =
				{
				-1.0f, -1.0f, 0.0f,
				1.0f, -1.0f, 0.0f,
				1.0f, 1.0f, 0.0f,
				-1.0f, 1.0f, 0.0f

				};

			GLfloat		vertices_rectangle [] =
				{
				-0.5f, 0.5f, 1.0f, 0.0f, 0.0f, // Top-left
				0.5f, 0.5f, 0.0f, 1.0f, 0.0f, // Top-right
				0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // Bottom-right
				-0.5f, -0.5f, 1.0f, 1.0f, 1.0f  // Bottom-left
				};

			GLushort	indices_square [] =
				{
				0, 1, 2,
				2, 0, 3
				}; //bottom

			GLushort	 indices_rectangle [] =
				{
				0, 1, 2,
				2, 3, 0
				};

			GLfloat		colorsA [] =
				{
				0.67f, 0.3f, 0.3f, 0.2f,
				0.47f, 0.3f, 0.3f, 0.2f,
				0.37f, 0.3f, 0.3f, 0.2f,
				0.57f, 0.1f, 0.9f, 0.5f

				};

			GLfloat		colorsB [] =
				{
				0.583f, 0.771f, 0.014f, 1.0f,
				0.609f, 0.115f, 0.436f, 1.0f,
				0.327f, 0.483f, 0.844f, 1.0f,
				1.0f, 0.0f, 0.0f, 1.0f


				};

			GLfloat texture_coordinates [] = {
				1.0f, 0.0f,
				0.0f, 0.0f,
				0.0f, 1.0f,
				1.0f, 1.0f
				};
			Menu_name = Amplify_Layer->GetActiveLevel ().LevelName;
			Enemies = Amplify_Layer->GetActiveLevel ().AI;
			Human = Amplify_Layer->GetActiveLevel ().Human;
			Input = Amplify_Layer->GetActiveLevel ().Input;
			Enemies_count = Amplify_Layer->GetActiveLevel ().AI_count;
			bg_tex = Amplify_Layer->GetActiveLevel ( ).background_tex;
			AI_tex = Amplify_Layer->GetActiveLevel ( ).AI_tex;
			std::cout << "debug:" << std::endl;
			std::cout << "Menu_name" << Menu_name << std::endl;
			std::cout << "Enemies" << Enemies << std::endl;
			std::cout << "Human" << Human << std::endl;
			std::cout << "Input" << Input << std::endl;
			std::cout << "Enemies_count" << Enemies_count << std::endl;
			//Init Enemies if needed
			AIs.clear ();
			ammo.clear ();
			Text = new TextObject ( Core_window, vertices_square, indices_square, colorsB, texture_coordinates );
			Text->Initialise_controls ( );
			Text->Enable_shader ( ); //problem
			Background1 = new Background ( Core_window, vertices_square, indices_square, colorsB, texture_coordinates,bg_tex );
			Background1->Initialise_controls ( );
			Background1->Enable_shader ( );
			if ( Enemies == true )
				{
				for ( int i = 0; i < Enemies_count; i++ )
					{
					AIs.emplace_back ( Core_window, vertices_square, indices_square, colorsB, texture_coordinates,AI_tex );
					AIs.back ().Initialise_controls ();
					AIs.back ().Enable_shader ();
					}
				}

			if ( Human == true )
				{
				
				
				Player1 = new Player ( Core_window, vertices_square, indices_square, colorsB, texture_coordinates );
				Player1->Initialise_controls ();
				Player1->Enable_shader ();
				for ( int i = 0; i < 10; i++ )
					{
					ammo.emplace_back ( Player1->get_player_position ( ), Player1->get_direction_for_bullet ( ), 0.05f, 0, uidz );
					uidz++;
					ammo.back ( ).set_vars ( Core_window, vertices_square, indices_square, colorsB, texture_coordinates );
					ammo.back ( ).Initialise_controls ( );
					ammo.back ( ).Enable_shader ( );
					}
				
				
				}
			}


			//Player1 = new Player ( Core_window, vertices_square, indices_square, colorsB, texture_coordinates );
			//AI1 = new AI ( Core_window, vertices_square, indices_square, colorsB, texture_coordinates );
			//AI2 = new AI ( Core_window, vertices_square, indices_square, colorsB, texture_coordinates );
			//Text = new TextObject ( Core_window, vertices_square, indices_square, colorsB, texture_coordinates );

			//Background1 = new Background ( Core_window, vertices_square, indices_square, colorsB, texture_coordinates );
			//for ( int i = 0; i < 10; i++ )
			//	{
			//	ammo.emplace_back ( Player1->get_player_position ( ), Player1->get_direction_for_bullet ( ), 0.05f, 0, uidz );
			//	uidz++;
			//	ammo.back ( ).set_vars ( Core_window, vertices_square, indices_square, colorsB, texture_coordinates );
			//	ammo.back ( ).Initialise_controls ( );
			//	ammo.back ( ).Enable_shader ( );
			//	}

			//Player1->Initialise_controls ( );
			//AI1->Initialise_controls ( );
			//AI2->Initialise_controls ( );
			//Background1->Initialise_controls ( );
			//Text->Initialise_controls ( );

			//Player1->Enable_shader ( );
			//AI1->Enable_shader ( );
			//AI2->Enable_shader ( );
			//Background1->Enable_shader ( );
			//Text->Enable_shader ( ); //problem
			//SoundEngine->play2D ( "private_libraries/sounds/themetime.mp3", GL_TRUE );
			//SoundEngine->setSoundVolume ( 0.4 );
			

		void Running::Amplify_Visuals ()
			{
			//int     LevelID;  // ID handle of the level
			//std::string LevelName;       // Name of the level
			//bool AI;    // AI Toggle
			//bool Human;    // Human Toggle
			//bool Input;	   // Keyboard Input Toggle
			//int AI_count; // number of AI instances
			//bool Active;
			

			}

		GLboolean Running::CheckCollision ( AI &one, Projectile &two ) // AABB - AABB collision
			{
			// Collision x-axis?
			bool collisionX = one.position.x + one.Object_controls.return_size_x ( ) / (Core_window_width/2) >= two.projectile_position.x &&
				two.projectile_position.x + two.Object_controls.return_size_x ( ) / (Core_window_width/2) >= one.position.x;
			std::cout << collisionX;
			// Collision y-axis?
			bool collisionY = one.position.y+ one.Object_controls.return_size_y ( )/(Core_window_height/2) <= two.projectile_position.y &&
				two.projectile_position.y+ two.Object_controls.return_size_y ( )/(Core_window_height/2) >= one.position.y;
			std::cout << collisionY;
			// Collision only if on both axes
			return collisionX && collisionY;
			}
		void Running::DoCollisions ()
			{
			std::list<Projectile>::iterator i = ammo.begin ( );
			while ( i != ammo.end ( ) )		
				{
				if ( (*i).active == true )
					{
					//docollision
					std::list<AI>::iterator k = AIs.begin ();
					while ( k != AIs.end () )
						{
						if ( (*k).destroyed == false )
							{

							if ( CheckCollision ( (*k), (*i) ) )
								{
								(*i).active = false;
								(*k).destroyed = true;
								Update_Score ();
								}
							}
							++k;
						}
					++i;
					}
				else
					{
					++i;
					}

				}
			}
			
		int Running::AI_remaining ()
			{
			AIs_remaining = AIs.size ();
			std::list<AI>::iterator k = AIs.begin ( );
			while ( k != AIs.end ( ) )
				{
				if ( (*k).destroyed == true )
					{
					AIs_remaining--;
					}
				++k;
				}
			return AIs_remaining;
			}

		void Running::GLHelpers_Init ()
			{
			
			}

		Running::~Running ()
			{
			ammo.clear();
			}

		bool Running::is_on ()
			{
			if ( Core_window->closed () )
				return 0;
			else
				return 1;
			}
		void Running::launch_projectile ()
			{
			
			std::list<Projectile>::iterator i = ammo.begin ( );
			while ( i != ammo.end ( ))
				{
				if ( (*i).active== false )
					{
					(*i).active = true;			
					projectiles_used++;
					(*i).Reinit_pos ( Player1->get_player_position () );					
					(*i).Initialise_controls ();
					
					SoundEngine->play2D ( shootSound, GL_FALSE );
					//launcher->setVolume ( 0.1 );
					
					
					break;
					}
					++i;
				}
			}
		void Running::update_projectiles ( )
			{
	
			std::list<Projectile>::iterator k = ammo.begin ( );
			while ( k != ammo.end ( ))
				{		
				if ( (*k).active == true )
					{
					(*k).steps++;					
					++k;
					}
				else
					{
					++k;
					}
					
				}
			}


		void Running::update_enemies ()
			{
			std::list<AI>::iterator k = AIs.begin ( );
			while ( k != AIs.end ( ) )
				{
				(*k).Update ();
				++k;
				}
			}
		void Running::display_projectiles ()
			{
			number_of_bullets = 10;
			std::list<Projectile>::iterator j = ammo.begin ( );
			while ( j != ammo.end ( ) )
				{
				if ( (*j)._Should_draw())
					{										
					(*j)._To_screen ( );					
					++j;
					number_of_bullets--;
					}
				else
					{
					++j;
					}
				}
			}
		void Running::display_enemies ( )
			{
			
			std::list<AI>::iterator j = AIs.begin ( );
			while ( j != AIs.end ( ) )
				{
				(*j).To_screen ();
				++j;
				}
			}


		void Running::update_graphics (double elapsed)
			{
			Background1->To_screen ( );
			if ( Menu_name == "Main Menu" )
				{
				Text->render_text ( "Welcome", 1.0f, Core_window_width * 2 / 100, Core_window_height * 90 / 100, 0, "Welcome to Amplify!" );
				Text->render_text ( "Welcome", 0.4f, Core_window_width * 2 / 100, Core_window_height * 95 / 100, 0, "Press enter to continue..." );
				}
			if (Menu_name == "Game Over")
				{
					Text->render_text("Welcome", 1.0f, Core_window_width * 45 / 100, Core_window_height * 5 / 100, 0, "CREDITS");
					Text->render_text("Welcome", 1.2f, Core_window_width * 44 / 100, Core_window_height * 15 / 100, 0, "Amplify!");
					Text->render_text("Welcome", 0.6f, Core_window_width * 30 / 100, Core_window_height * 20 / 100, 0, "Developed by Simple Computer Programs: Entertainment");
					Text->render_text("Score", 0.5f, Core_window_width * 20 / 100, Core_window_height * 30 / 100, current_score, "Congratulations! Your score was: ");
					Text->render_text("Score", 0.5f, Core_window_width * 20 / 100, Core_window_height * 40 / 100, NULL, "Please enter your name: " + Playername);
					if (Highscores.size() > 0)
					{
						Text->render_text("Score", 0.6f, Core_window_width * 20 / 100, Core_window_height * 50 / 100, NULL, "Top Scores");
						int k = 0; k++;
						int delim = 55;
						for (int i = 0; i<Highscores.size();i++)
						{
							if (k < 10)
							{
								delim += 5;
								Text->render_text("Score", 0.4f, Core_window_width * 20 / 100, Core_window_height * delim / 100, NULL, std::to_string(k)+". "+Highscores[i]);
								k++;
							}

						}
					}
				}
			if ( Human == 1 )
				{
				
				Player1->To_screen ( );
				display_projectiles ( );
				
				Text->render_text ( "Bullets", 0.5f, Core_window_width * 2 / 100, Core_window_height * 90 / 100, number_of_bullets, " bullets left" );
				Text->render_text ( "Score", 0.5f, Core_window_width * 2 / 100, Core_window_height * 85 / 100, current_score, "Score: " );
				Text->render_text ( "AIS", 0.5f, Core_window_width * 2 / 100, Core_window_height * 95 / 100, AI_remaining(), " Enemies left" );
				Text->render_text ( "FPS", 0.3f, Core_window_width * 90 / 100, Core_window_height * 5 / 100, 1000 / elapsed, "FPS:" );
				}
			if ( Enemies == 1 )
				{
				display_enemies ( );
				//AI1->To_screen ( );
				//AI2->To_screen ( );
				}

			
			Core_window->update ();
			}

		void Running::Update_Score ()
			{
			if ( projectiles_used < 11 )
				multiplier = 5;
			if ( projectiles_used >= 11 && projectiles_used < 20 )
				multiplier = 4;
			if ( projectiles_used >= 20 && projectiles_used < 30 )
				multiplier = 2;
			if ( projectiles_used > 30 )
				multiplier = 1;

			current_score = current_score + (multiplier*AI_value);
			}
		void Running::Reset_Score ()
			{
			current_score = 0;
			projectiles_used = 0;
			Playername = "";
			score_saved = false;
			Highscores.clear();
			}

		}
	}