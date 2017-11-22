#include "Input.h"

namespace Erebos
	{
	namespace graphics{
		Input::Input ( Running* running_object )
			{
			game = running_object;
			input_step = 0;
			}

		void Input::process_input ()
			{
			if ( game->Enemies == 1 )
				{
				if ( game->Player1->check_click ( ))
					{
					game->launch_projectile ();
					input_step=125;		
					};				
				}
			}
		void Input::clear ()
			{
			game->Core_window->clear ( );
			
			}
		void Input::reset_input ()
			{
			input_step -= 17;
			}

		bool Input::input_ready ()
			{
			if ( input_step <= 0 )
				{
				return true;
				}
			return false;
			}
		void Input::update_game_state ()
			{

			if ( game->Enemies == 1 )
				{
				game->DoCollisions ();
				//game->AI1->Update ( );
				//game->AI2->Update ();
				game->update_enemies ();
				}
			if ( game->Human == 1 )
				{
				game->Player1->Update ( );
				game->Background1->Update ();
				game->update_projectiles ( );			
				}
			if ( game->Menu_name == "Game Over" &&game->Core_window->Can_retrieve () )
				{
				if ( game->Core_window->Retrieve_text ( ) != -1 )
				game->Playername += game->Core_window->Retrieve_text ();
				if ( game->Core_window->Retrieve_text ( ) ==-2)
					game->Playername = " ";
				}
			else if (game->Menu_name == "Game Over" && game->Core_window->done == true)
			{
				if (game->all_registered == false)
				{
					FileUtils::write_score(game->Playername, game->current_score);
					FileUtils::read_score(game->Highscores);
				}
				game->all_registered = true;
				
			}
			else
				game->all_registered = false;
			}

		Input::~Input ()
			{
			delete game;
			}

		}
	}