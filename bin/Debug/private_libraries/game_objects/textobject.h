#pragma once
#include "GameObject.h"
#include <ft2build.h>
#include FT_FREETYPE_H
#include <map>
#include	<glm.hpp>

#include </PerPriDev/Amplify-2D/Dependencies/GLM/include/gtc/type_ptr.hpp>

namespace Erebos{
	namespace graphics{
		using	namespace	maths;

		class TextObject : public GameObject
			{
			protected:
				float position_x;
				float position_y;
				FT_Face face;
				FT_Library ft;
				FT_GlyphSlot g;

				struct Character{
					GLuint     TextureID;  // ID handle of the glyph texture
					glm::ivec2 Size;       // Size of glyph
					glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
					GLuint     Advance;    // Offset to advance to next glyph				
					};
				std::map<GLchar, Character> Characters;
				Buffer Object_buffer;
				GLfloat x;
				GLfloat y;

			public:
				TextObject ( Window* window, GLfloat vertices [12], GLushort indices [6], GLfloat colors [16], GLfloat texture_coords [8] );
				
				void Initialise_controls ( );
				void To_screen ( );
				void Enable_shader ();
				void Draw ();
				void Compute_matrices ();
				void Init_FreeType();
				void Init_CharacterMap();
				void render_text ( std::string type,GLfloat scale,int x,int y,int value,std::string text);
			};



		}
	}
