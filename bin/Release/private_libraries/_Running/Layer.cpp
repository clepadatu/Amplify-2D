#include "Layer.h"



namespace Erebos
{
	namespace graphics{
		

		Layer::Layer()
		{
			std::vector<int> levelids = { 0, 1, 2 };
			std::vector<std::string>levelnames = { "Main Menu", "Play", "Game Over" };
			std::vector<bool> AIs = {0,1,0};
			std::vector<bool> Humans = {0,1,0};
			std::vector<bool> Inputs = {1,1,1};
			std::vector<int> aicount = {0,10,0};
			std::vector<int> active= { 1, 0, 0 };
			std::vector<int> complete= { 0, 0, 0 };
			std::vector<const char*> background_tex= { "private_libraries/textures/bg_mm.jpg", "private_libraries/textures/nebula1920_1080.jpg", "private_libraries/textures/credits.jpg" };
			std::vector<const char*> AI_tex= { "", "private_libraries/textures/SS1.png", "" };

			for (int i = 0; i < levelids.size(); i++)
			{
				Level Temporary_level =
				{
					levelids[i],
					levelnames[i],
					AIs[i],
					Humans[i],
					Inputs[i],
					aicount[i],
					active[i],
					complete [i],
					background_tex [i],
					AI_tex [i]

				};
				if ( active[i] == 1 )
					{
					ActiveLevel.Active = active [i];
					ActiveLevel.AI = AIs [i];
					ActiveLevel.AI_count = aicount [i];
					ActiveLevel.Human = Humans [i];
					ActiveLevel.Input = Inputs [i];
					ActiveLevel.LevelID = levelids [i];
					ActiveLevel.LevelName = levelnames [i];
					ActiveLevel.Completed =  complete[i];
					ActiveLevel.background_tex= background_tex[i];
					ActiveLevel.AI_tex = AI_tex [i];
					}
				Levels.insert(std::pair<int, Level>(levelids[i], Temporary_level));
			
				
			}
			//printout();
				
			
		}
		void Layer::printout()
		{
			std::cout << "==Debug==> Menus initialisation listing:" << std::endl;
			
			for (int i = 0; i < Levels.size(); i++)
			{
				Level temp = Levels[i];
				std::cout << "==> MenuID=" << temp.LevelID << std::endl;
				std::cout << "==> Menu name=" << temp.LevelName<< std::endl;\
					std::cout << "==> AI Enabled=" << temp.AI<< std::endl;
				std::cout << "==> Human Enabled=" << temp.Human<< std::endl;
				std::cout << "==> Input Enabled=" << temp.Input<< std::endl;
				std::cout << "==> AI #count=" << temp.AI_count<< std::endl;
				std::cout << "==> AI Texture=" << temp.AI_tex<< std::endl;
				std::cout << "==> Background Texture=" << temp.background_tex<< std::endl;
				std::cout << "==> Menu Active=" << temp.Active << std::endl;				
				std::cout << "==> Completed=" << temp.Completed<< std::endl;
				std::cout << std::endl;
			}
		}

		void Layer::SetActiveLevel ( int new_lvl_id, int old_lvl_id )
			{
			std::cout << "debug:" << std::endl;
			Levels [old_lvl_id].Active = 0;
			std::cout << "old_lvl_id=" << Levels [old_lvl_id].Active << std::endl;
			Levels [new_lvl_id].Active = 1;
			std::cout << "new_lvl_id=" << Levels [new_lvl_id].Active << std::endl;
			
					ActiveLevel.Active = Levels [new_lvl_id].Active;
					ActiveLevel.LevelID = Levels [new_lvl_id].LevelID;
					ActiveLevel.LevelName = Levels [new_lvl_id].LevelName;
					ActiveLevel.Human = Levels [new_lvl_id].Human;
					ActiveLevel.Input = Levels [new_lvl_id].Input;
					ActiveLevel.AI = Levels [new_lvl_id].AI;
					ActiveLevel.AI_count = Levels [new_lvl_id].AI_count;
					ActiveLevel.AI_tex= Levels [new_lvl_id].AI_tex;
					ActiveLevel.background_tex= Levels [new_lvl_id].background_tex;
					ActiveLevel.Completed = Levels [new_lvl_id].Completed;

					std::cout << "New level data:"<<std::endl;
					std::cout << "==> MenuID=" << ActiveLevel.LevelID << std::endl;
					std::cout << "==> Menu name=" << ActiveLevel.LevelName << std::endl; \
						std::cout << "==> AI Enabled=" << ActiveLevel.AI << std::endl;
					std::cout << "==> Human Enabled=" << ActiveLevel.Human << std::endl;
					std::cout << "==> Input Enabled=" << ActiveLevel.Input << std::endl;
					std::cout << "==> AI #count=" << ActiveLevel.AI_count << std::endl;
					std::cout << "==> AI Texture=" << ActiveLevel.AI_tex<< std::endl;
					std::cout << "==> Background Texture=" << ActiveLevel.background_tex<< std::endl;
					std::cout << "==> Menu Active=" << ActiveLevel.Active << std::endl;
					std::cout << "==> Completed=" << ActiveLevel.Completed << std::endl;
					std::cout << std::endl;
					
			}

			int Layer::GetActiveLevel_ID ()
				{
				return ActiveLevel.LevelID;
				}
			Layer::Level Layer::GetActiveLevel ()
				{
				return ActiveLevel;
				}
			bool Layer::Check_Level ()
				{
				if ( ActiveLevel.Completed == true )
					{
					switch ( ActiveLevel.LevelID )
						{
							case 0:
								{
								SetActiveLevel ( 1, 0 );
								break;
								}
							case 1:
								{
								SetActiveLevel ( 2, 1 );
								break;
								}
							case 2:
								{
								SetActiveLevel ( 0, 2 );
								break;
								}
						}
					return true;
					}
				else
					return false;

				}
			void Layer::Complete_Level ()
				{
				ActiveLevel.Completed = true;
				}










































		void Layer::Read_level_data_inprogress_complex()
		{
					
			std::string Leveldata = FileUtils::read_file("private_libraries/_Running/Levels.dat");
			std::cout << "Leveldata:\n" << Leveldata << std::endl;

			//Find line breaks
			std::vector<std::size_t> positions; // holds all positions of new line breaks; effectively number of levels/lines
			size_t pos = Leveldata.find("\n", 0);
			while (pos != std::string::npos)
			{
				positions.push_back(pos);
				pos = Leveldata.find("\n", pos + 1);
			}
			positions.push_back(350);
			std::cout << "Positions size is=" << positions.size() << std::endl;
			std::cout << "Indexes of newlines: " << std::endl;
			std::copy(positions.begin(), positions.end(),std::ostream_iterator<int>(std::cout, "\n"));
			
			////Split lines
			std::vector<std::string> SubLevelData;
			for (int i = 0; i < positions.size(); i++)
			{
				if (i==0)
					SubLevelData.push_back(Leveldata.substr(0, positions[0]));
				else
				{

					std::cout << "start:" << positions[i - 1] + 1 << ",length:" << positions[i] - 1 <<",result:"<<std::endl;
					if (positions[i] == 350)
						std::cout<<Leveldata.substr(positions[i - 1] + 1, std::string::npos)<<std::endl;
					else
						std::cout << Leveldata.substr(positions[i - 1] + 1, positions[i] - positions[i - 1]-1) << std::endl;

					if (positions[i]==350)
						SubLevelData.push_back(Leveldata.substr(positions[i - 1] + 1, std::string::npos));
					else
						SubLevelData.push_back(Leveldata.substr(positions[i - 1] + 1, positions[i]-positions[i-1]-1));
				}
					
			}

			//Split and register each line/component into the level struct
			for (int i = 0; i < SubLevelData.size(); i++)
			{
				std::cout << "Line[" << i << "]=" << SubLevelData[i] << std::endl;
				std::cout << std::endl;
				std::vector<std::size_t> comma_pos;
				size_t detect = SubLevelData[i].find(",", 0);
				
				while (detect != std::string::npos)
				{
					comma_pos.push_back(detect);
					detect = SubLevelData[i].find(",", detect + 1);
				}
				comma_pos.push_back(999);
				std::vector<std::string> SingleLevel;
				for (int i = 0; i < comma_pos.size(); i++)
				{
					if (i == 0)
						SingleLevel.push_back(SubLevelData[i].substr(0, comma_pos[0]));
					else
					{
						if (comma_pos[i] == 999)
							SingleLevel.push_back(SubLevelData[i].substr(comma_pos[i - 1] + 1, std::string::npos));
						else
							SingleLevel.push_back(SubLevelData[i].substr(comma_pos[i - 1] + 1, comma_pos[i] - comma_pos[i - 1] - 1));
					}
						
				}
				for (int i = 0; i < SingleLevel.size(); i++)
					std::cout << SingleLevel[i] << std::endl;
				

			}
			/*std::cout << "Vector lines contents: " << std::endl;
			std::copy(SubLevelData.begin(), SubLevelData.end(), std::ostream_iterator<std::string>(std::cout, ";"));*/
		}
		






	}
}
