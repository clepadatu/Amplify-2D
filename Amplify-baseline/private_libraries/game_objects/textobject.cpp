#include "textobject.h"

TextObject::TextObject( Window* window, GLfloat vertices [12], GLushort indices [6], GLfloat colors [16], GLfloat texture_coords [8] )
	{

	Init_FreeType();
	Init_CharacterMap();

	x = 10;
	y = 30;
	Main_window = window;
	O_vertices = vertices;
	O_indices = indices;
	O_colors = colors;
	O_texture_coordinates = texture_coords;

	//Object_buffer.AddBuffer_text(NULL, sizeof(GLfloat)* 6 * 4, 4);
	//Object.addBuffer_text(&Object_buffer,0);//alternative use as below, new buffer inside first parameter;

	Object.addBuffer_text ( new Buffer ( NULL,  6 * 4, 4,1 ), 0 );

	//Object_ibo.set_properties_dynamic ( O_indices, 24 ); wrong
	//Object.addBuffer ( new Buffer ( O_vertices, 4 * 3, 3 ), 0 );
	//Object.addBuffer ( new Buffer ( O_colors, 4 * 4, 4 ), 1 );
	//Object.addBuffer ( new Buffer ( O_texture_coordinates, 4 * 2, 2 ), 2 );

	//Initialise_texture ( );
	}


void TextObject::Initialise_controls ( )
	{
	window_width = Main_window->getWidth ( );
	window_height = Main_window->getHeight ( );
	Main_window->getMousePosition ( mouse_x, mouse_y );
	type = 0;
	Object_controls.set_init_text ( window_width, window_height, type, mouse_x, mouse_y );
	
	//Object_controls.set_init_and_pos_and_size ( window_width, window_height, type, mouse_x, mouse_y, 245.0f, 245.0f, 1280, 720, 90.0f );

	};

void TextObject::To_screen ( )
	{
	this->Compute_matrices ( );	
	}

void TextObject::Compute_matrices ( )
	{
	glm::mat4 MVP = Object_controls.getProjectionMatrix();
	glUniformMatrix4fv ( Object_shader.getUniformLocation ( "TextposM" ), 1, GL_FALSE, glm::value_ptr ( MVP ));
	}
void TextObject::Enable_shader ()
	{
	Object_shader.Initialise_shader ( "private_libraries/shaders/FTtext.vert", "private_libraries/shaders/FTtext.frag" );
	Object_shader.enable ( );
	}



void TextObject::render_text(std::string type,GLfloat scale,int x,int y,int value,std::string text)
	{
	Object_shader.enable ( );
	
	if ( type=="Bullets" || type=="AIS")
		{
		text = std::to_string(value) + text;
		}
	if (type=="FPS" || type=="Score")
		{
		if (value != NULL)
			{
			text = text + std::to_string(value);
			}
		}
	To_screen ( );
	Object.bind ( );
	Object_shader.setUniform3f("textColor", maths::vec3(0.5f, 0.8f, 0.2f));

	glActiveTexture(GL_TEXTURE0);
	
	
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		Character ch = Characters[*c];

		GLfloat xpos = x + ch.Bearing.x * scale;
		GLfloat ypos = y + (this->Characters ['H'].Bearing.y - ch.Bearing.y) * scale;

		GLfloat w = ch.Size.x * scale;
		GLfloat h = ch.Size.y * scale;
		// Update VBO for each character
		GLfloat vertices [6][4] = {
			{ xpos, ypos + h, 0.0, 1.0 },
			{ xpos + w, ypos, 1.0, 0.0 },
			{ xpos, ypos, 0.0, 0.0 },

			{ xpos, ypos + h, 0.0, 1.0 },
			{ xpos + w, ypos + h, 1.0, 1.0 },
			{ xpos + w, ypos, 1.0, 0.0 }
			};
		// Render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		// Update content of VBO memory
		Object.testbind ();
			//glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData ( GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices ); // Be sure to use glBufferSubData and not glBufferData

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// Render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
		
	}	
	Object.testunbind ();
	Object.unbind ();
	

	}


void TextObject::Draw ()
	{
	

	}














void TextObject::Init_FreeType(){
	if (FT_Init_FreeType(&ft))
	{
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
	}

	
	if (FT_New_Face(ft, "private_libraries/fonts/LucidaSansRegular.ttf", 0, &face))
	{
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
	}
	FT_Set_Pixel_Sizes(face, 0, 48);


}

void TextObject::Init_CharacterMap(){
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

	for (GLubyte c = 0; c < 128; c++)
	{
		// Load character glyph 
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			continue;
		}
		// Generate texture
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
			);
		// Set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// Now store character for later use
		Character character = {
			texture,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x
		};
		Characters.insert(std::pair<GLchar, Character>(c, character));
	}
	FT_Done_Face(face);
	FT_Done_FreeType(ft);
	glBindTexture(GL_TEXTURE_2D, 0);
}
