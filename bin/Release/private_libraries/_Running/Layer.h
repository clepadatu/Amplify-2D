#pragma once
#include "../window/window.h"
//#include "../___Game_Object/Game_Object.h"
#include <string>
//#include "Running.h"
#include <time.h>
#include <string>
#include <vector>
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

namespace Erebos
{
	namespace graphics{


		class Layer
		{
		protected:
			//Level structure
			struct Level{
				int     LevelID;  // ID handle of the level
				std::string LevelName;       // Name of the level
				bool AI;    // AI Toggle
				bool Human;    // Human Toggle
				bool Input;	   // Keyboard Input Toggle
				int AI_count; // number of AI instances
				bool Active;
				bool Completed;
				const char* background_tex;
				const char* AI_tex;
			};
			//Active loaded level
			Level ActiveLevel;
			//Loaded level map
			std::map<int, Level> Levels;
			
		public:
			//load Map of Levels manually
			Layer();
			~Layer();
			//debug info, see all mapped levels
			void printout();
			//switch from one level to another
			void SetActiveLevel ( int new_lvl_id, int old_lvl_id );
			//return current active level ID
			int GetActiveLevel_ID ();
			Level GetActiveLevel ();
			bool Check_Level ();
			void Complete_Level ();
			void Read_level_data_inprogress_complex();//external level loader, tbd
		};
	}
}