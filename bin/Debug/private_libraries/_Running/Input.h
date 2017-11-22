#pragma once
#include "../window/window.h"
//#include "../___Game_Object/Game_Object.h"
#include <string>
#include "Running.h"
#include <time.h>
namespace Erebos
	{
	namespace graphics{


		class Input
			{
			protected:
			
			public:
				Running* game;
				int input_step;
				Input ( Running* running_object );
				~Input ();
				void process_input ();
				void update_game_state ();
				bool input_ready ();
				void clear ();
				void reset_input ();
			};
		}
	}