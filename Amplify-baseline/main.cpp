#include "private_libraries\_Running\Running.h"
#include "private_libraries\_Running\Input.h"
#include "private_libraries\_Running\Layer.h"
#include <time.h>




int		main ( )
	{
	using	namespace	Erebos;
	using	namespace	graphics;
	using	namespace	maths;
	using namespace irrklang;

	//===========Globals that need to be defined==============
	double current, elapsed;
	double previous = clock ( );
	double lag = 0.0;
	//=====================Globals End========================
	srand ( time ( NULL ) );


	//==============Pre-main Initialising sequence============
	Layer* level = new Layer();
	Running* game = new Running (level );
	Input* input = new Input ( game );
	int temper = 5000;
	//=====================End Initialisation=================




	//==============Main Loop=================================
	while ( game->is_on ( ) )
		{
		current = clock ( );
		elapsed = current - previous;
		previous = current;
		lag += elapsed;
	//	std::cout << "Seconds per frame is: " << elapsed << "ms" << std::endl;
		
		//----------Process Input-----------
		input->clear ();
		if ( input->input_ready () )
			{
			input->process_input ();
			}
		temper--;
		
		//-----------goes here--------------
		//------------End Input-------------


		//-----------Update Game------------
		while ( lag >= 17 )
			{

			input->update_game_state ( );
			lag -= 17;
			input->reset_input ();
			}
		//-----------End Update-------------




		//--------------Render--------------

		game->update_graphics ( elapsed);
		if ( game->Menu_name=="Main Menu" && input->game->Core_window->isKeyPressed(257))
			{
			game->Core_window->Disable_text_receive();//make sure no text input
			game->Amplify_Layer->Complete_Level ();
			game->Amplify_Layer->Check_Level ();
			game->Set_Amplify_Visuals ();
			std::cout << "ended";			
			}
		if ( game->Menu_name == "Play" && (game->AI_remaining ( ) == 0 || input->game->Core_window->isKeyPressed ( 256 )) )
			{
			game->Core_window->Enable_text_receive();//enable text input			
			game->Amplify_Layer->Complete_Level ( );
			game->Amplify_Layer->Check_Level ( );
			game->Set_Amplify_Visuals ( );
			std::cout << "ended";
			temper = 65535;
			}
		if ( game->Menu_name == "Game Over" && (temper == 0 || input->game->Core_window->isKeyPressed ( 256 )))
			{
			game->Core_window->Disable_text_receive();//make sure no text input
			game->Amplify_Layer->Complete_Level ( );
			game->Amplify_Layer->Check_Level ( );
			game->Set_Amplify_Visuals ( );
			std::cout << "ended";
			game->Reset_Score ();
			}
			
		//-------End Render-----------------


		}
	//============Main Loop End; terminate further============
	
	return 0;

	}

